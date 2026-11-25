#define CYBORG_EXPORTS
#include "cyborg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <shlobj.h>

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")

#define CYBORG_CJSON_DLL_NAME      "dc2cjson.dll"
#define CYBORG_PATH_WRAP_DLL_NAME  "dc2path.dll"

typedef void* DCPATH_HANDLE;

#define DCP_ROOT_CUSTOM      0
#define DCP_ROOT_WORKSPACE   1
#define DCP_ROOT_EXECUTABLE  2
#define DCP_ROOT_SYSTEM_TEMP 3

/* dc_cjson.dll exports */
typedef void*       (__stdcall *PFN_CJ_LoadFile)(const char *filePath);
typedef void        (__stdcall *PFN_CJ_Destroy)(void *root);
typedef int         (__stdcall *PFN_CJ_HasPath)(void *root, const char *path);
typedef const char* (__stdcall *PFN_CJ_GetString)(void *root, const char *path, const char *fallback);

/* dc_path_wrap.dll exports (LIBRARY dc_path_wrap @1..@11) */
typedef void          (__stdcall *PFN_DCP_SetDefaultRoots)(const char* workspaceFallback, const char* customFallback);
typedef void          (__stdcall *PFN_DCP_SetDelimiters)(const char* pathSep, const char* appendSep);
typedef DCPATH_HANDLE (__stdcall *PFN_DCP_Create)(int rootType, const char* customRoot);
typedef void          (__stdcall *PFN_DCP_Destroy)(DCPATH_HANDLE ctx);
typedef void          (__stdcall *PFN_DCP_SetRoot)(DCPATH_HANDLE ctx, const char* path);
typedef void          (__stdcall *PFN_DCP_SetPrepend)(DCPATH_HANDLE ctx, const char* prependStr);
typedef void          (__stdcall *PFN_DCP_SetAppend)(DCPATH_HANDLE ctx, const char* appendStr);
typedef const char*   (__stdcall *PFN_DCP_GetRoot)(DCPATH_HANDLE ctx);
typedef int           (__stdcall *PFN_DCP_BuildPath)(DCPATH_HANDLE ctx, const char* rawTarget, char* outBuffer, int maxOutLen);
typedef int           (__stdcall *PFN_DCP_SplitExt)(const char* filename, char* outBase, int baseMax, char* outExt, int extMax);
typedef int           (__stdcall *PFN_DCP_AmendExt)(const char* filename, const char* ext, char* outBuffer, int maxOutLen);

typedef struct CyborgPathWrap {
    HMODULE               hMod;
    PFN_DCP_SetDefaultRoots SetDefaultRoots;
    PFN_DCP_SetDelimiters   SetDelimiters;
    PFN_DCP_Create          Create;
    PFN_DCP_Destroy         Destroy;
    PFN_DCP_SetRoot         SetRoot;
    PFN_DCP_SetPrepend      SetPrepend;
    PFN_DCP_SetAppend       SetAppend;
    PFN_DCP_GetRoot         GetRoot;
    PFN_DCP_BuildPath       BuildPath;
    PFN_DCP_SplitExt        SplitExt;
    PFN_DCP_AmendExt        AmendExt;
} CyborgPathWrap;

static char g_ConfigPath[CYBORG_MAX_STR] = "";

static int LoadPathWrap(CyborgPathWrap *pw) {
    ZeroMemory(pw, sizeof(*pw));
    pw->hMod = LoadLibraryA(CYBORG_PATH_WRAP_DLL_NAME);
    if (!pw->hMod) {
        printf("[ERROR] Failed to load %s (Error: %lu)\n", CYBORG_PATH_WRAP_DLL_NAME, GetLastError());
        return 0;
    }

    pw->SetDefaultRoots = (PFN_DCP_SetDefaultRoots)GetProcAddress(pw->hMod, "DCP_SetDefaultRoots");
    pw->SetDelimiters   = (PFN_DCP_SetDelimiters)GetProcAddress(pw->hMod, "DCP_SetDelimiters");
    pw->Create          = (PFN_DCP_Create)GetProcAddress(pw->hMod, "DCP_Create");
    pw->Destroy         = (PFN_DCP_Destroy)GetProcAddress(pw->hMod, "DCP_Destroy");
    pw->SetRoot         = (PFN_DCP_SetRoot)GetProcAddress(pw->hMod, "DCP_SetRoot");
    pw->SetPrepend      = (PFN_DCP_SetPrepend)GetProcAddress(pw->hMod, "DCP_SetPrepend");
    pw->SetAppend       = (PFN_DCP_SetAppend)GetProcAddress(pw->hMod, "DCP_SetAppend");
    pw->GetRoot         = (PFN_DCP_GetRoot)GetProcAddress(pw->hMod, "DCP_GetRoot");
    pw->BuildPath       = (PFN_DCP_BuildPath)GetProcAddress(pw->hMod, "DCP_BuildPath");
    pw->SplitExt        = (PFN_DCP_SplitExt)GetProcAddress(pw->hMod, "DCP_SplitExt");
    pw->AmendExt        = (PFN_DCP_AmendExt)GetProcAddress(pw->hMod, "DCP_AmendExt");

    if (!pw->Create || !pw->Destroy || !pw->SetRoot || !pw->BuildPath) {
        printf("[ERROR] Missing required exports in %s.\n", CYBORG_PATH_WRAP_DLL_NAME);
        FreeLibrary(pw->hMod);
        ZeroMemory(pw, sizeof(*pw));
        return 0;
    }

    if (pw->SetDelimiters) {
        pw->SetDelimiters("\\", "_");
    }
    if (pw->SetDefaultRoots) {
        pw->SetDefaultRoots(".", ".");
    }
    return 1;
}

static void UnloadPathWrap(CyborgPathWrap *pw) {
    if (pw && pw->hMod) {
        FreeLibrary(pw->hMod);
        ZeroMemory(pw, sizeof(*pw));
    }
}

static void StripQuotesAndTrim(const char *src, char *dst, size_t dstSize) {
    if (!src || !dst || dstSize == 0) return;

    const char *start = src;
    while (*start == ' ' || *start == '\t' || *start == '"' ||
           ((unsigned char)*start == 0xEF && (unsigned char)start[1] == 0xBB && (unsigned char)start[2] == 0xBF)) {
        if ((unsigned char)*start == 0xEF) {
            start += 3;
        } else {
            start++;
        }
    }

    size_t len = strlen(start);
    while (len > 0 && (start[len - 1] == '"' || start[len - 1] == ' ' ||
                       start[len - 1] == '\t' || start[len - 1] == ',' ||
                       start[len - 1] == '\r' || start[len - 1] == '\n')) {
        len--;
    }

    if (len >= dstSize) len = dstSize - 1;
    memcpy(dst, start, len);
    dst[len] = '\0';
}

static void NormalizePath(const char *src, char *dst, size_t dstSize) {
    char temp[CYBORG_MAX_STR];
    StripQuotesAndTrim(src, temp, sizeof(temp));

    size_t j = 0;
    for (size_t i = 0; temp[i] != '\0' && j < dstSize - 1; i++) {
        if (temp[i] == '\\' && temp[i + 1] == '\\') {
            dst[j++] = '\\';
            i++;
        } else if (temp[i] == '/') {
            dst[j++] = '\\';
        } else {
            dst[j++] = temp[i];
        }
    }
    dst[j] = '\0';
}

static void GetDirectoryWithSlash(const char *filePath, char *outDir, size_t outSize) {
    strcpy_s(outDir, outSize, filePath ? filePath : "");
    char *lastSlash = strrchr(outDir, '\\');
    char *lastFwd   = strrchr(outDir, '/');
    if (lastFwd > lastSlash) lastSlash = lastFwd;
    if (lastSlash) {
        *(lastSlash + 1) = '\0';
    } else {
        outDir[0] = '\0';
    }
}

static void EnsureDirectoryExists(const char *dirPath) {
    if (!dirPath || dirPath[0] == '\0') return;
    char norm[CYBORG_MAX_STR];
    NormalizePath(dirPath, norm, sizeof(norm));
    size_t len = strlen(norm);
    while (len > 3 && norm[len - 1] == '\\') {
        norm[--len] = '\0';
    }
    if (norm[0] != '\0') {
        SHCreateDirectoryExA(NULL, norm, NULL);
    }
}

static void EnsureParentDirectoryExists(const char *filePath) {
    if (!filePath || filePath[0] == '\0') return;
    char parentDir[CYBORG_MAX_STR];
    GetDirectoryWithSlash(filePath, parentDir, sizeof(parentDir));
    if (parentDir[0] != '\0') {
        EnsureDirectoryExists(parentDir);
    }
}

static int ResolveWithContext(CyborgPathWrap *pw, DCPATH_HANDLE ctx,
                              const char *fallbackBaseDir, const char *src,
                              char *out, size_t outSize) {
    if (!src || src[0] == '\0') {
        if (out && outSize > 0) out[0] = '\0';
        return 0;
    }

    char cleanSrc[CYBORG_MAX_STR];
    NormalizePath(src, cleanSrc, sizeof(cleanSrc));

    if (pw && pw->hMod && pw->BuildPath && ctx) {
        if (pw->BuildPath(ctx, cleanSrc, out, (int)outSize)) {
            NormalizePath(out, out, outSize);
            return 1;
        }
    }

    if ((isalpha((unsigned char)cleanSrc[0]) && cleanSrc[1] == ':') || cleanSrc[0] == '\\' || cleanSrc[0] == '/') {
        strcpy_s(out, outSize, cleanSrc);
    } else {
        char baseNorm[CYBORG_MAX_STR];
        NormalizePath(fallbackBaseDir ? fallbackBaseDir : "", baseNorm, sizeof(baseNorm));
        size_t bLen = strlen(baseNorm);
        if (bLen > 0 && baseNorm[bLen - 1] != '\\') {
            sprintf_s(out, outSize, "%s\\%s", baseNorm, cleanSrc);
        } else {
            sprintf_s(out, outSize, "%s%s", baseNorm, cleanSrc);
        }
    }
    NormalizePath(out, out, outSize);
    return 1;
}

static int RunProcessTool(const char *exePath, const char *args) {
    char cmdLine[CYBORG_MAX_STR * 4];
    sprintf_s(cmdLine, sizeof(cmdLine), "\"%s\" %s", exePath, args);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        printf("[ERROR] Failed to execute: %s (Error: %lu)\n", exePath, GetLastError());
        return -1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return (int)exitCode;
}

static int LocateSdkTool(const char *exeName, char *outPath) {
    if (SearchPathA(NULL, exeName, NULL, CYBORG_MAX_STR, outPath, NULL) > 0) return 1;

    char sdkRoot[CYBORG_MAX_STR] = "";
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots", 0, KEY_READ | KEY_WOW64_32KEY, &hKey) == ERROR_SUCCESS ||
        RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD bufSize = sizeof(sdkRoot);
        RegQueryValueExA(hKey, "KitsRoot10", NULL, NULL, (LPBYTE)sdkRoot, &bufSize);
        RegCloseKey(hKey);
    }
    if (sdkRoot[0] == '\0') return 0;

    size_t len = strlen(sdkRoot);
    if (len > 0 && sdkRoot[len - 1] == '\\') sdkRoot[len - 1] = '\0';

    char searchPattern[CYBORG_MAX_STR];
    sprintf_s(searchPattern, sizeof(searchPattern), "%s\\bin\\*", sdkRoot);

    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPattern, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && fd.cFileName[0] != '.') {
                sprintf_s(outPath, CYBORG_MAX_STR, "%s\\bin\\%s\\x64\\%s", sdkRoot, fd.cFileName, exeName);
                if (GetFileAttributesA(outPath) != INVALID_FILE_ATTRIBUTES) {
                    FindClose(hFind);
                    return 1;
                }
            }
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
    }
    return 0;
}

static int ParseCatalogManifest(const char *iniPath,
                                char *outResultDir, size_t resDirSize,
                                char *outCatName, size_t catNameSize,
                                char targets[][CYBORG_MAX_STR],
                                char keys[][128],
                                int maxTargets) {
    FILE *f = NULL;
    if (fopen_s(&f, iniPath, "r") != 0 || !f) return 0;

    char line[1024];
    int section = 0;
    int count = 0;

    while (fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\r' || line[len - 1] == '\n')) line[--len] = '\0';

        char *start = line;
        while (*start == ' ' || *start == '\t') start++;
        if (*start == '\0' || *start == ';' || *start == '#') continue;

        if (*start == '[') {
            if (_strnicmp(start, "[CatalogHeader]", 15) == 0) section = 1;
            else if (_strnicmp(start, "[CatalogFiles]", 14) == 0 ||
                     _strnicmp(start, "[TargetFiles]", 13) == 0 ||
                     _strnicmp(start, "[Files]", 7) == 0) section = 2;
            else section = 0;
            continue;
        }

        char *eq = strchr(start, '=');
        if (!eq) continue;

        *eq = '\0';
        char keyBuf[128];
        StripQuotesAndTrim(start, keyBuf, sizeof(keyBuf));
        char *valRaw = eq + 1;

        if (section == 1) {
            if (_stricmp(keyBuf, "ResultDir") == 0 && outResultDir) {
                NormalizePath(valRaw, outResultDir, resDirSize);
            } else if (_stricmp(keyBuf, "Name") == 0 && outCatName) {
                NormalizePath(valRaw, outCatName, catNameSize);
            }
        } else if (section == 2 || section == 0) {
            if (count < maxTargets) {
                NormalizePath(valRaw, targets[count], CYBORG_MAX_STR);
                if (targets[count][0] != '\0') {
                    if (keys) {
                        strcpy_s(keys[count], 128, keyBuf[0] ? keyBuf : "<HASH>file");
                    }
                    count++;
                }
            }
        }
    }

    fclose(f);
    return count;
}

static int BuildCdfFile(const char *cdfPath,
                        const char *catFileName,
                        const char *resultDir,
                        char targets[][CYBORG_MAX_STR],
                        char keys[][128],
                        int targetCount) {
    EnsureParentDirectoryExists(cdfPath);
    EnsureDirectoryExists(resultDir);

    FILE *fp = NULL;
    if (fopen_s(&fp, cdfPath, "wb") != 0 || !fp) return 0;

    fprintf(fp, "[CatalogHeader]\r\n");
    fprintf(fp, "Name=%s\r\n", catFileName);
    fprintf(fp, "ResultDir=%s\r\n", resultDir);
    fprintf(fp, "PublicVersion=0x00000001\r\n");
    fprintf(fp, "CatalogVersion=2\r\n");
    fprintf(fp, "HashAlgorithms=SHA256\r\n\r\n");
    fprintf(fp, "[CatalogFiles]\r\n");

    for (int i = 0; i < targetCount; i++) {
        const char *k = (keys && keys[i][0] != '\0') ? keys[i] : NULL;
        if (k) {
            fprintf(fp, "%s=%s\r\n", k, targets[i]);
        } else {
            fprintf(fp, "<HASH>file%d=%s\r\n", i + 1, targets[i]);
        }
    }

    fclose(fp);
    return 1;
}

static void EscapePsSingleQuotes(const char *src, char *dst, size_t dstSize) {
    size_t j = 0;
    for (size_t i = 0; src && src[i] != '\0' && j + 1 < dstSize; i++) {
        if (src[i] == '\'') {
            if (j + 2 < dstSize) {
                dst[j++] = '\'';
                dst[j++] = '\'';
            }
        } else {
            dst[j++] = src[i];
        }
    }
    dst[j] = '\0';
}

static int GenerateSelfSignedPfx(const char *pfxPath, const char *subject, const char *password) {
    EnsureParentDirectoryExists(pfxPath);

    char escSubject[CYBORG_MAX_STR * 2];
    char escPassword[CYBORG_MAX_STR * 2];
    char escPfx[CYBORG_MAX_STR * 2];

    EscapePsSingleQuotes(subject, escSubject, sizeof(escSubject));
    EscapePsSingleQuotes(password, escPassword, sizeof(escPassword));
    EscapePsSingleQuotes(pfxPath, escPfx, sizeof(escPfx));

    char psCmd[CYBORG_MAX_STR * 4];
    sprintf_s(psCmd, sizeof(psCmd),
        "-NoProfile -ExecutionPolicy Bypass -Command \""
        "$cert = New-SelfSignedCertificate -Type CodeSigningCert -Subject '%s' -CertStoreLocation 'Cert:\\CurrentUser\\My'; "
        "$pwd = ConvertTo-SecureString -String '%s' -Force -AsPlainText; "
        "Export-PfxCertificate -Cert $cert -FilePath '%s' -Password $pwd | Out-Null; "
        "Import-PfxCertificate -FilePath '%s' -CertStoreLocation 'Cert:\\CurrentUser\\Root' -Password $pwd | Out-Null\"",
        escSubject, escPassword, escPfx, escPfx);

    return (RunProcessTool("powershell.exe", psCmd) == 0) ? 1 : 0;
}

static void ReadJsonField(PFN_CJ_GetString pGetStr, void *root, const char *prefix,
                          const char *fieldName, char *destBuf, size_t destSize, int isPath) {
    char keyPath[256];
    sprintf_s(keyPath, sizeof(keyPath), "%s%s", prefix, fieldName);
    const char *val = pGetStr(root, keyPath, NULL);
    if (val && val[0] != '\0') {
        if (isPath) {
            NormalizePath(val, destBuf, destSize);
        } else {
            strcpy_s(destBuf, destSize, val);
        }
    }
}

CYBORG_API int __stdcall Cyborg_LoadConfigFromJson(const char *jsonPath, CyborgSignConfig *outCfg) {
    if (!jsonPath || !outCfg) return 0;
    ZeroMemory(outCfg, sizeof(CyborgSignConfig));
    g_ConfigPath[0] = '\0';

    CyborgPathWrap pw;
    int hasPw = LoadPathWrap(&pw);
    char resolvedJsonPath[CYBORG_MAX_STR] = "";
    if (hasPw) {
        DCPATH_HANDLE jsonCtx = pw.Create(DCP_ROOT_EXECUTABLE, NULL);
        if (jsonCtx) {
            ResolveWithContext(&pw, jsonCtx, "", jsonPath, resolvedJsonPath, sizeof(resolvedJsonPath));
            pw.Destroy(jsonCtx);
        }
    }
    const char *targetJson = (resolvedJsonPath[0] != '\0') ? resolvedJsonPath : jsonPath;

    HMODULE hCjson = LoadLibraryA(CYBORG_CJSON_DLL_NAME);
    if (!hCjson) {
        printf("[ERROR] Could not load %s to parse JSON config.\n", CYBORG_CJSON_DLL_NAME);
        if (hasPw) UnloadPathWrap(&pw);
        return 0;
    }

    PFN_CJ_LoadFile  pCJ_LoadFile  = (PFN_CJ_LoadFile)GetProcAddress(hCjson, "CJ_LoadFile");
    PFN_CJ_Destroy   pCJ_Destroy   = (PFN_CJ_Destroy)GetProcAddress(hCjson, "CJ_Destroy");
    PFN_CJ_HasPath   pCJ_HasPath   = (PFN_CJ_HasPath)GetProcAddress(hCjson, "CJ_HasPath");
    PFN_CJ_GetString pCJ_GetString = (PFN_CJ_GetString)GetProcAddress(hCjson, "CJ_GetString");
    if (!pCJ_LoadFile || !pCJ_Destroy || !pCJ_HasPath || !pCJ_GetString) {
        printf("[ERROR] Missing exports in %s.\n", CYBORG_CJSON_DLL_NAME);
        FreeLibrary(hCjson);
        if (hasPw) UnloadPathWrap(&pw);
        return 0;
    }

    void *root = pCJ_LoadFile(targetJson);
    if (!root) {
        printf("[ERROR] %s failed to parse JSON file: %s\n", CYBORG_CJSON_DLL_NAME, targetJson);
        FreeLibrary(hCjson);
        if (hasPw) UnloadPathWrap(&pw);
        return 0;
    }

    const char *prefix = pCJ_HasPath(root, "Config") ? "Config." : "";
    char pathField[CYBORG_MAX_STR] = "";
    ReadJsonField(pCJ_GetString, root, prefix, "Path",      pathField, sizeof(pathField), 1);
    if (pathField[0] == '\0') ReadJsonField(pCJ_GetString, root, prefix, "BasePath",  pathField, sizeof(pathField), 1);
    if (pathField[0] == '\0') ReadJsonField(pCJ_GetString, root, prefix, "cert_path", pathField, sizeof(pathField), 1);
    if (pathField[0] != '\0') {
        strcpy_s(g_ConfigPath, sizeof(g_ConfigPath), pathField);
    }

    ReadJsonField(pCJ_GetString, root, prefix, "Title",        outCfg->title,        sizeof(outCfg->title),        0);
    ReadJsonField(pCJ_GetString, root, prefix, "TimestampUrl", outCfg->timestampUrl, sizeof(outCfg->timestampUrl), 0);
    ReadJsonField(pCJ_GetString, root, prefix, "cert_cat",     outCfg->certCat,      sizeof(outCfg->certCat),      1);
    ReadJsonField(pCJ_GetString, root, prefix, "cert_ini",     outCfg->certIni,      sizeof(outCfg->certIni),      1);
    ReadJsonField(pCJ_GetString, root, prefix, "cert_cdf",     outCfg->certCdf,      sizeof(outCfg->certCdf),      1);
    ReadJsonField(pCJ_GetString, root, prefix, "cert_reset",   outCfg->certReset,    sizeof(outCfg->certReset),    0);
    ReadJsonField(pCJ_GetString, root, prefix, "cert_name",    outCfg->certName,     sizeof(outCfg->certName),     1);
    ReadJsonField(pCJ_GetString, root, prefix, "Subject",      outCfg->subject,      sizeof(outCfg->subject),      0);
    ReadJsonField(pCJ_GetString, root, prefix, "Password",     outCfg->password,     sizeof(outCfg->password),     0);

    pCJ_Destroy(root);
    FreeLibrary(hCjson);
    if (hasPw) UnloadPathWrap(&pw);
    return 1;
}

CYBORG_API int __stdcall Cyborg_SignFromConfig(const CyborgSignConfig *cfg, const char *baseDir, int forceNewCert) {
    if (!cfg) return 0;

    CyborgPathWrap pw;
    if (!LoadPathWrap(&pw)) {
        return 0;
    }

    char effectiveBase[CYBORG_MAX_STR] = "";
    if (baseDir && baseDir[0] != '\0') {
        NormalizePath(baseDir, effectiveBase, sizeof(effectiveBase));
    } else if (g_ConfigPath[0] != '\0') {
        NormalizePath(g_ConfigPath, effectiveBase, sizeof(effectiveBase));
    }

    int rootType = (effectiveBase[0] != '\0') ? DCP_ROOT_CUSTOM : DCP_ROOT_EXECUTABLE;
    DCPATH_HANDLE ctx = pw.Create(rootType, (rootType == DCP_ROOT_CUSTOM) ? effectiveBase : NULL);
    if (!ctx) {
        printf("[ERROR] Failed to create path context via %s.\n", CYBORG_PATH_WRAP_DLL_NAME);
        UnloadPathWrap(&pw);
        return 0;
    }

    char makecatPath[CYBORG_MAX_STR]  = "";
    char signtoolPath[CYBORG_MAX_STR] = "";

    if (!LocateSdkTool("makecat.exe", makecatPath) || !LocateSdkTool("signtool.exe", signtoolPath)) {
        printf("[ERROR] Could not locate makecat.exe or signtool.exe in Windows SDK.\n");
        pw.Destroy(ctx);
        UnloadPathWrap(&pw);
        return 0;
    }

    char iniPath[CYBORG_MAX_STR], cdfPath[CYBORG_MAX_STR], catPath[CYBORG_MAX_STR], pfxPath[CYBORG_MAX_STR];
    ResolveWithContext(&pw, ctx, effectiveBase, cfg->certIni,  iniPath, sizeof(iniPath));
    ResolveWithContext(&pw, ctx, effectiveBase, cfg->certCdf,  cdfPath, sizeof(cdfPath));
    ResolveWithContext(&pw, ctx, effectiveBase, cfg->certCat,  catPath, sizeof(catPath));
    ResolveWithContext(&pw, ctx, effectiveBase, cfg->certName, pfxPath, sizeof(pfxPath));

    char manifestResDir[CYBORG_MAX_STR] = "";
    char manifestCatName[CYBORG_MAX_STR] = "";
    static char targets[CYBORG_MAX_FILES][CYBORG_MAX_STR];
    static char keys[CYBORG_MAX_FILES][128];

    int fileCount = ParseCatalogManifest(
        iniPath,
        manifestResDir, sizeof(manifestResDir),
        manifestCatName, sizeof(manifestCatName),
        targets, keys, CYBORG_MAX_FILES
    );
    if (fileCount <= 0) {
        printf("[ERROR] No target files found in manifest: %s\n", iniPath);
        pw.Destroy(ctx);
        UnloadPathWrap(&pw);
        return 0;
    }

    for (int i = 0; i < fileCount; i++) {
        char resolved[CYBORG_MAX_STR];
        ResolveWithContext(&pw, ctx, effectiveBase, targets[i], resolved, sizeof(resolved));
        strcpy_s(targets[i], CYBORG_MAX_STR, resolved);
    }

    char finalResultDir[CYBORG_MAX_STR] = "";
    if (manifestResDir[0] != '\0') {
        ResolveWithContext(&pw, ctx, effectiveBase, manifestResDir, finalResultDir, sizeof(finalResultDir));
    } else {
        GetDirectoryWithSlash(catPath, finalResultDir, sizeof(finalResultDir));
    }
    size_t rLen = strlen(finalResultDir);
    if (rLen > 0 && finalResultDir[rLen - 1] == '\\') {
        finalResultDir[rLen - 1] = '\0';
    }
    EnsureDirectoryExists(finalResultDir);

    const char *catBaseName = strrchr(catPath, '\\');
    catBaseName = catBaseName ? (catBaseName + 1) : catPath;

    int needCert = forceNewCert || (_stricmp(cfg->certReset, "yes") == 0) ||
                   (GetFileAttributesA(pfxPath) == INVALID_FILE_ATTRIBUTES);

    if (needCert) {
        printf("[INFO] Generating self-signed PFX certificate: %s\n", pfxPath);
        if (!GenerateSelfSignedPfx(pfxPath, cfg->subject, cfg->password)) {
            printf("[ERROR] Failed to generate PFX certificate.\n");
            pw.Destroy(ctx);
            UnloadPathWrap(&pw);
            return 0;
        }
    }

    if (cdfPath[0] == '\0') {
        if (pw.AmendExt && pw.AmendExt(iniPath, ".cdf", cdfPath, (int)sizeof(cdfPath))) {
            /* amended extension */
        } else {
            sprintf_s(cdfPath, sizeof(cdfPath), "%s.cdf", iniPath);
        }
    }
    if (!BuildCdfFile(cdfPath, catBaseName, finalResultDir, targets, keys, fileCount)) {
        printf("[ERROR] Failed to write CDF file: %s\n", cdfPath);
        pw.Destroy(ctx);
        UnloadPathWrap(&pw);
        return 0;
    }

    char makecatArgs[CYBORG_MAX_STR * 2];
    sprintf_s(makecatArgs, sizeof(makecatArgs), "-v \"%s\"", cdfPath);
    if (RunProcessTool(makecatPath, makecatArgs) != 0) {
        printf("[ERROR] makecat.exe failed building catalog.\n");
        pw.Destroy(ctx);
        UnloadPathWrap(&pw);
        return 0;
    }

    char finalCatFull[CYBORG_MAX_STR];
    sprintf_s(finalCatFull, sizeof(finalCatFull), "%s\\%s", finalResultDir, catBaseName);

    char signArgs[CYBORG_MAX_STR * 4];
    sprintf_s(signArgs, sizeof(signArgs),
        "sign /f \"%s\" /p \"%s\" /fd SHA256 /tr \"%s\" /td SHA256 /d \"%s\" \"%s\"",
        pfxPath, cfg->password, cfg->timestampUrl, cfg->title, finalCatFull);

    if (RunProcessTool(signtoolPath, signArgs) != 0) {
        printf("[ERROR] signtool.exe failed signing catalog: %s\n", finalCatFull);
        pw.Destroy(ctx);
        UnloadPathWrap(&pw);
        return 0;
    }

    for (int i = 0; i < fileCount; i++) {
        sprintf_s(signArgs, sizeof(signArgs),
            "sign /f \"%s\" /p \"%s\" /fd SHA256 /tr \"%s\" /td SHA256 /d \"%s\" \"%s\"",
            pfxPath, cfg->password, cfg->timestampUrl, cfg->title, targets[i]);
        if (RunProcessTool(signtoolPath, signArgs) != 0) {
            printf("[WARN] signtool.exe failed on target: %s\n", targets[i]);
        }
    }

    printf("[SUCCESS] Signed catalog and %d target file(s).\n", fileCount);
    pw.Destroy(ctx);
    UnloadPathWrap(&pw);
    return 1;
}

CYBORG_API int __stdcall Cyborg_SignFromJson(const char *jsonPath, int forceNewCertOverride) {
    CyborgSignConfig cfg;
    if (!Cyborg_LoadConfigFromJson(jsonPath, &cfg)) {
        printf("[ERROR] Failed to load JSON config: %s\n", jsonPath ? jsonPath : "(null)");
        return 0;
    }
    char baseDir[CYBORG_MAX_STR];
    if (g_ConfigPath[0] != '\0') {
        strcpy_s(baseDir, sizeof(baseDir), g_ConfigPath);
    } else {
        GetDirectoryWithSlash(jsonPath, baseDir, sizeof(baseDir));
    }
    return Cyborg_SignFromConfig(&cfg, baseDir, forceNewCertOverride);
}

CYBORG_API int __stdcall Cyborg_RunCli(int argc, char **argv) {
    const char *jsonPath = NULL;
    int forceNew = 0;

    for (int i = 1; i < argc; i++) {
        if (_stricmp(*(argv + i), "--config") == 0 && (i + 1) < argc) {
            jsonPath = *(argv + (++i));
        } else if (_stricmp(*(argv + i), "--new-cert") == 0) {
            forceNew = 1;
        }
    }

    if (!jsonPath) {
        printf("Usage: cyborg.exe --config <path_to_json> [--new-cert]\n");
        return 1;
    }

    return Cyborg_SignFromJson(jsonPath, forceNew) ? 0 : 1;
}