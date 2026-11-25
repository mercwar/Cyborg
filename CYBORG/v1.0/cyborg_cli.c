#include "cyborg.h"
#include <windows.h>
#include <wintrust.h>
#include <softpub.h>
#include <wincrypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "wintrust.lib")
#pragma comment(lib, "crypt32.lib")

#define CYBORG_DLL_NAME     "cyborg.dll"
#define CYBORG_CJSON_DLL    "dc_cjson.dll"
#define IDI_APP_ICON        101
#define CLI_MAX_FILES       256

typedef int (__stdcall *PFN_Cyborg_LoadConfigFromJson)(const char *jsonPath, CyborgSignConfig *outCfg);
typedef int (__stdcall *PFN_Cyborg_SignFromConfig)(const CyborgSignConfig *cfg, const char *baseDir, int forceNewCert);
typedef int (__stdcall *PFN_Cyborg_SignFromJson)(const char *jsonPath, int forceNewCertOverride);
typedef int (__stdcall *PFN_Cyborg_RunCli)(int argc, char **argv);

typedef void*       (__stdcall *PFN_CJ_LoadFile)(const char *filePath);
typedef void        (__stdcall *PFN_CJ_Destroy)(void *root);
typedef int         (__stdcall *PFN_CJ_HasPath)(void *root, const char *path);
typedef const char* (__stdcall *PFN_CJ_GetString)(void *root, const char *path, const char *fallback);

typedef struct CyborgDllApi {
    HMODULE hMod;
    char    resolvedPath[MAX_PATH];
    PFN_Cyborg_LoadConfigFromJson LoadConfigFromJson;
    PFN_Cyborg_SignFromConfig     SignFromConfig;
    PFN_Cyborg_SignFromJson       SignFromJson;
    PFN_Cyborg_RunCli             RunCli;
} CyborgDllApi;

typedef struct CliFileEntry {
    char role[32];
    char path[CYBORG_MAX_STR];
} CliFileEntry;

static WORD g_DefaultAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
static int  g_HasConsoleAttr = 0;

static void InitConsoleStyle(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE && hOut != NULL) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
            g_DefaultAttr = csbi.wAttributes;
            g_HasConsoleAttr = 1;
        }
    }
}

static void SetColor(WORD attr) {
    if (!g_HasConsoleAttr) return;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE && hOut != NULL) {
        SetConsoleTextAttribute(hOut, attr);
    }
}

static void ResetColor(void) {
    if (!g_HasConsoleAttr) return;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE && hOut != NULL) {
        SetConsoleTextAttribute(hOut, g_DefaultAttr);
    }
}

static void LogTag(const char *tag, WORD color, const char *fmt, ...) {
    va_list args;
    SetColor(color);
    printf("[%s] ", tag);
    ResetColor();
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

static void PrintBanner(void) {
    SetColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("====================================================================\n");
    printf("  MERCWAR AI :: CYBORG DIGITAL SIGNATURE CLI (v1.1)\n");
    printf("====================================================================\n");
    ResetColor();
}

static void ApplyConsoleIcon(void) {
    HWND hConsole = GetConsoleWindow();
    if (!hConsole) return;

    HINSTANCE hInst = GetModuleHandleA(NULL);
    HICON hBig = (HICON)LoadImageA(hInst, MAKEINTRESOURCEA(IDI_APP_ICON),
                                   IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
    HICON hSmall = (HICON)LoadImageA(hInst, MAKEINTRESOURCEA(IDI_APP_ICON),
                                     IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);

    if (hBig)   SendMessageA(hConsole, WM_SETICON, ICON_BIG, (LPARAM)hBig);
    if (hSmall) SendMessageA(hConsole, WM_SETICON, ICON_SMALL, (LPARAM)hSmall);
}

static int FileExistsA(const char *path) {
    if (!path || path[0] == '\0') return 0;
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
}

static HMODULE TryLoadCandidate(const char *candidate, char *outPath, size_t outSize) {
    if (!candidate || candidate[0] == '\0') return NULL;
    HMODULE h = LoadLibraryA(candidate);
    if (h) {
        if (GetModuleFileNameA(h, outPath, (DWORD)outSize) == 0) {
            strcpy_s(outPath, outSize, candidate);
        }
        return h;
    }
    return NULL;
}

static int LoadCyborgDll(const char *dllPath, CyborgDllApi *api) {
    ZeroMemory(api, sizeof(*api));

    HMODULE hMod = NULL;
    char exeDir[MAX_PATH] = "";
    char sysDir[MAX_PATH] = "";
    char wowDir[MAX_PATH] = "";
    char candidate[MAX_PATH] = "";

    GetModuleFileNameA(NULL, exeDir, MAX_PATH);
    char *lastSlash = strrchr(exeDir, '\\');
    if (lastSlash) *(lastSlash + 1) = '\0';

    GetSystemDirectoryA(sysDir, MAX_PATH);

    typedef UINT (WINAPI *PFN_GetSysWow64DirectoryA)(LPSTR, UINT);
    PFN_GetSysWow64DirectoryA pGetWow64 =
        (PFN_GetSysWow64DirectoryA)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetSystemWow64DirectoryA");
    if (pGetWow64) {
        pGetWow64(wowDir, MAX_PATH);
    }

    if (dllPath && dllPath[0] != '\0' && _strcmpi(dllPath, CYBORG_DLL_NAME) != 0) {
        LogTag("INFO", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Loading specified DLL: %s", dllPath);
        hMod = TryLoadCandidate(dllPath, api->resolvedPath, sizeof(api->resolvedPath));
    } else {
        if (exeDir[0] != '\0') {
            sprintf_s(candidate, sizeof(candidate), "%s%s", exeDir, CYBORG_DLL_NAME);
            if (FileExistsA(candidate)) {
                hMod = TryLoadCandidate(candidate, api->resolvedPath, sizeof(api->resolvedPath));
            }
        }
        if (!hMod && sysDir[0] != '\0') {
            sprintf_s(candidate, sizeof(candidate), "%s\\%s", sysDir, CYBORG_DLL_NAME);
            if (FileExistsA(candidate)) {
                hMod = TryLoadCandidate(candidate, api->resolvedPath, sizeof(api->resolvedPath));
            }
        }
        if (!hMod && wowDir[0] != '\0') {
            sprintf_s(candidate, sizeof(candidate), "%s\\%s", wowDir, CYBORG_DLL_NAME);
            if (FileExistsA(candidate)) {
                hMod = TryLoadCandidate(candidate, api->resolvedPath, sizeof(api->resolvedPath));
            }
        }
        if (!hMod) {
            hMod = TryLoadCandidate(CYBORG_DLL_NAME, api->resolvedPath, sizeof(api->resolvedPath));
        }
    }

    if (!hMod) {
        DWORD err = GetLastError();
        LogTag("ERROR", FOREGROUND_RED | FOREGROUND_INTENSITY,
               "Failed to load %s (Win32 Error: %lu)",
               (dllPath && dllPath[0]) ? dllPath : CYBORG_DLL_NAME, err);
        LogTag("INFO", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Searched: EXE dir (%s), System32 (%s), and PATH. Pass --dll <path> if needed.",
               exeDir[0] ? exeDir : ".", sysDir[0] ? sysDir : "System32");
        return 0;
    }

    api->hMod = hMod;
    api->LoadConfigFromJson = (PFN_Cyborg_LoadConfigFromJson)GetProcAddress(api->hMod, "Cyborg_LoadConfigFromJson");
    api->SignFromConfig     = (PFN_Cyborg_SignFromConfig)GetProcAddress(api->hMod, "Cyborg_SignFromConfig");
    api->SignFromJson       = (PFN_Cyborg_SignFromJson)GetProcAddress(api->hMod, "Cyborg_SignFromJson");
    api->RunCli             = (PFN_Cyborg_RunCli)GetProcAddress(api->hMod, "Cyborg_RunCli");

    if (!api->LoadConfigFromJson || !api->SignFromConfig || !api->SignFromJson || !api->RunCli) {
        LogTag("ERROR", FOREGROUND_RED | FOREGROUND_INTENSITY,
               "Missing required exports in %s:", api->resolvedPath);
        if (!api->LoadConfigFromJson) printf("    - Cyborg_LoadConfigFromJson\n");
        if (!api->SignFromConfig)     printf("    - Cyborg_SignFromConfig\n");
        if (!api->SignFromJson)       printf("    - Cyborg_SignFromJson\n");
        if (!api->RunCli)             printf("    - Cyborg_RunCli\n");
        FreeLibrary(api->hMod);
        ZeroMemory(api, sizeof(*api));
        return 0;
    }

    LogTag("OK", FOREGROUND_GREEN | FOREGROUND_INTENSITY,
           "Loaded DLL: %s", api->resolvedPath);
    return 1;
}

static void UnloadCyborgDll(CyborgDllApi *api) {
    if (api && api->hMod) {
        FreeLibrary(api->hMod);
        ZeroMemory(api, sizeof(*api));
    }
}

static void TrimAndNormPath(const char *src, char *dst, size_t dstSize) {
    if (!src || !dst || dstSize == 0) return;
    while (*src == ' ' || *src == '\t' || *src == '"') src++;
    size_t len = strlen(src);
    while (len > 0 && (src[len - 1] == '"' || src[len - 1] == ' ' ||
                       src[len - 1] == '\t' || src[len - 1] == '\r' || src[len - 1] == '\n')) {
        len--;
    }
    if (len >= dstSize) len = dstSize - 1;
    memcpy(dst, src, len);
    dst[len] = '\0';
    for (size_t i = 0; dst[i] != '\0'; i++) {
        if (dst[i] == '/') dst[i] = '\\';
    }
}

static void CombinePath(const char *baseDir, const char *relOrAbs, char *out, size_t outSize) {
    char p[CYBORG_MAX_STR];
    TrimAndNormPath(relOrAbs, p, sizeof(p));
    if (p[0] == '\0') {
        out[0] = '\0';
        return;
    }
    if ((isalpha((unsigned char)p[0]) && p[1] == ':') || (p[0] == '\\' && p[1] == '\\')) {
        strcpy_s(out, outSize, p);
        return;
    }
    char b[CYBORG_MAX_STR];
    TrimAndNormPath(baseDir ? baseDir : "", b, sizeof(b));
    size_t bLen = strlen(b);
    while (bLen > 3 && b[bLen - 1] == '\\') b[--bLen] = '\0';
    while (p[0] == '\\') memmove(p, p + 1, strlen(p));
    if (bLen > 0) {
        sprintf_s(out, outSize, "%s\\%s", b, p);
    } else {
        strcpy_s(out, outSize, p);
    }
}

static void ExtractDirWithSlash(const char *filePath, char *outDir, size_t outSize) {
    if (!filePath || !outDir || outSize == 0) return;
    strcpy_s(outDir, outSize, filePath);
    char *lastSlash = strrchr(outDir, '\\');
    char *lastFwd   = strrchr(outDir, '/');
    if (lastFwd > lastSlash) lastSlash = lastFwd;
    if (lastSlash) {
        *(lastSlash + 1) = '\0';
    } else {
        outDir[0] = '\0';
    }
}

static int ComputeFileSha256Hex(const char *filePath, char *hexOut, size_t hexSize) {
    if (!filePath || !hexOut || hexSize < 65) return 0;
    hexOut[0] = '\0';

    HANDLE hFile = CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return 0;

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    if (!CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        CloseHandle(hFile);
        return 0;
    }
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        CloseHandle(hFile);
        return 0;
    }

    BYTE buf[65536];
    DWORD bytesRead = 0;
    BOOL ok = TRUE;
    while (ReadFile(hFile, buf, sizeof(buf), &bytesRead, NULL) && bytesRead > 0) {
        if (!CryptHashData(hHash, buf, bytesRead, 0)) {
            ok = FALSE;
            break;
        }
    }

    BYTE hashBytes[32];
    DWORD hashLen = sizeof(hashBytes);
    if (ok && CryptGetHashParam(hHash, HP_HASHVAL, hashBytes, &hashLen, 0)) {
        static const char digits[] = "0123456789abcdef";
        for (DWORD i = 0; i < hashLen && (i * 2 + 1) < hexSize; i++) {
            hexOut[i * 2]     = digits[(hashBytes[i] >> 4) & 0x0F];
            hexOut[i * 2 + 1] = digits[hashBytes[i] & 0x0F];
        }
        hexOut[hashLen * 2] = '\0';
    } else {
        ok = FALSE;
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);
    return ok ? 1 : 0;
}

static const char* CheckAuthenticodeStatus(const char *filePath) {
    if (!filePath || !FileExistsA(filePath)) return "MISSING";

    size_t len = strlen(filePath);
    if (len >= 4 && (_strcmpi(filePath + len - 4, ".pfx") == 0 ||
                     _strcmpi(filePath + len - 4, ".ini") == 0 ||
                     _strcmpi(filePath + len - 4, ".cdf") == 0)) {
        return "N/A";
    }

    WCHAR wPath[MAX_PATH * 2];
    if (MultiByteToWideChar(CP_ACP, 0, filePath, -1, wPath, _countof(wPath)) == 0) {
        return "ERR";
    }

    WINTRUST_FILE_INFO fileData;
    ZeroMemory(&fileData, sizeof(fileData));
    fileData.cbStruct       = sizeof(fileData);
    fileData.pcwszFilePath  = wPath;

    GUID policyGuid = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    WINTRUST_DATA wtData;
    ZeroMemory(&wtData, sizeof(wtData));
    wtData.cbStruct          = sizeof(wtData);
    wtData.dwUIChoice        = WTD_UI_NONE;
    wtData.fdwRevocationChecks = WTD_REVOKE_NONE;
    wtData.dwUnionChoice     = WTD_CHOICE_FILE;
    wtData.pFile             = &fileData;
    wtData.dwStateAction     = WTD_STATEACTION_VERIFY;

    LONG status = WinVerifyTrust(NULL, &policyGuid, &wtData);

    wtData.dwStateAction = WTD_STATEACTION_CLOSE;
    WinVerifyTrust(NULL, &policyGuid, &wtData);

    if (status == ERROR_SUCCESS) return "VALID";
    if (status == TRUST_E_NOSIGNATURE) return "UNSIGNED";
    if (status == CERT_E_UNTRUSTEDROOT || status == TRUST_E_EXPLICIT_DISTRUST) return "SIGNED(UNTRUSTED)";
    return "SIGNED/OTHER";
}

static void PrintSingleFileInfo(const char *role, const char *fullPath) {
    WIN32_FILE_ATTRIBUTE_DATA fad;
    char sizeBuf[32] = "MISSING";
    char timeBuf[32] = "----/--/-- --:--:--";
    char shaBuf[65]  = "----------------------------------------------------------------";
    const char *sigStatus = "MISSING";

    if (fullPath && fullPath[0] != '\0' && GetFileAttributesExA(fullPath, GetFileExInfoStandard, &fad) &&
        !(fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        ULONGLONG fileSize = (((ULONGLONG)fad.nFileSizeHigh) << 32) | (ULONGLONG)fad.nFileSizeLow;
        sprintf_s(sizeBuf, sizeof(sizeBuf), "%llu B", fileSize);

        FILETIME ftLocal;
        SYSTEMTIME st;
        if (FileTimeToLocalFileTime(&fad.ftLastWriteTime, &ftLocal) &&
            FileTimeToSystemTime(&ftLocal, &st)) {
            sprintf_s(timeBuf, sizeof(timeBuf), "%04u-%02u-%02u %02u:%02u:%02u",
                      st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        }

        ComputeFileSha256Hex(fullPath, shaBuf, sizeof(shaBuf));
        sigStatus = CheckAuthenticodeStatus(fullPath);
    }

    SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  [%s] ", role);
    ResetColor();
    printf("%s\n", (fullPath && fullPath[0]) ? fullPath : "(none)");
    printf("      Size: %-14s | Modified: %-19s | Sig: %s\n", sizeBuf, timeBuf, sigStatus);
    printf("      SHA256: %s\n", shaBuf);
}

static void DiscoverAndPrintFiles(const char *jsonPath, const CyborgSignConfig *cfg, const char *baseDirArg) {
    char baseDir[CYBORG_MAX_STR] = "";
    char cfgPathField[CYBORG_MAX_STR] = "";

    HMODULE hCjson = LoadLibraryA(CYBORG_CJSON_DLL);
    if (hCjson) {
        PFN_CJ_LoadFile  pLoad  = (PFN_CJ_LoadFile)GetProcAddress(hCjson, "CJ_LoadFile");
        PFN_CJ_Destroy   pDest  = (PFN_CJ_Destroy)GetProcAddress(hCjson, "CJ_Destroy");
        PFN_CJ_HasPath   pHas   = (PFN_CJ_HasPath)GetProcAddress(hCjson, "CJ_HasPath");
        PFN_CJ_GetString pGetS  = (PFN_CJ_GetString)GetProcAddress(hCjson, "CJ_GetString");
        if (pLoad && pDest && pHas && pGetS && jsonPath) {
            void *root = pLoad(jsonPath);
            if (root) {
                const char *pfx = pHas(root, "Config") ? "Config." : "";
                char k1[128], k2[128], k3[128];
                sprintf_s(k1, sizeof(k1), "%sPath", pfx);
                sprintf_s(k2, sizeof(k2), "%sBasePath", pfx);
                sprintf_s(k3, sizeof(k3), "%scert_path", pfx);
                const char *v = pGetS(root, k1, NULL);
                if (!v || !v[0]) v = pGetS(root, k2, NULL);
                if (!v || !v[0]) v = pGetS(root, k3, NULL);
                if (v && v[0]) TrimAndNormPath(v, cfgPathField, sizeof(cfgPathField));
                pDest(root);
            }
        }
        FreeLibrary(hCjson);
    }

    if (baseDirArg && baseDirArg[0]) {
        TrimAndNormPath(baseDirArg, baseDir, sizeof(baseDir));
    } else if (cfgPathField[0]) {
        strcpy_s(baseDir, sizeof(baseDir), cfgPathField);
    } else {
        char exeDir[MAX_PATH] = "";
        GetModuleFileNameA(NULL, exeDir, MAX_PATH);
        ExtractDirWithSlash(exeDir, baseDir, sizeof(baseDir));
    }

    SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n  File & Artifact Details (Base: %s)\n", baseDir[0] ? baseDir : ".");
    printf("  ------------------------------------------------------------------\n");
    ResetColor();

    char pfxFull[CYBORG_MAX_STR] = "";
    char iniFull[CYBORG_MAX_STR] = "";
    char cdfFull[CYBORG_MAX_STR] = "";
    char catFull[CYBORG_MAX_STR] = "";

    CombinePath(baseDir, cfg->certName, pfxFull, sizeof(pfxFull));
    CombinePath(baseDir, cfg->certIni,  iniFull, sizeof(iniFull));
    CombinePath(baseDir, cfg->certCdf,  cdfFull, sizeof(cdfFull));
    CombinePath(baseDir, cfg->certCat,  catFull, sizeof(catFull));

    if (pfxFull[0]) PrintSingleFileInfo("PFX ", pfxFull);
    if (iniFull[0]) PrintSingleFileInfo("INI ", iniFull);
    if (cdfFull[0]) PrintSingleFileInfo("CDF ", cdfFull);
    if (catFull[0]) PrintSingleFileInfo("CAT ", catFull);

    if (iniFull[0] && FileExistsA(iniFull)) {
        FILE *f = NULL;
        if (fopen_s(&f, iniFull, "r") == 0 && f) {
            char line[1024];
            int inFiles = 0;
            int idx = 0;
            while (fgets(line, sizeof(line), f)) {
                size_t l = strlen(line);
                while (l > 0 && (line[l - 1] == '\r' || line[l - 1] == '\n')) line[--l] = '\0';
                char *s = line;
                while (*s == ' ' || *s == '\t') s++;
                if (*s == '\0' || *s == ';' || *s == '#') continue;
                if (*s == '[') {
                    inFiles = (_strnicmp(s, "[CatalogFiles]", 14) == 0 ||
                               _strnicmp(s, "[TargetFiles]", 13) == 0 ||
                               _strnicmp(s, "[Files]", 7) == 0);
                    continue;
                }
                if (inFiles) {
                    char *eq = strchr(s, '=');
                    if (eq) {
                        char targetRaw[CYBORG_MAX_STR];
                        char targetFull[CYBORG_MAX_STR];
                        char roleBuf[32];
                        TrimAndNormPath(eq + 1, targetRaw, sizeof(targetRaw));
                        CombinePath(baseDir, targetRaw, targetFull, sizeof(targetFull));
                        idx++;
                        sprintf_s(roleBuf, sizeof(roleBuf), "T%02d ", idx);
                        PrintSingleFileInfo(roleBuf, targetFull);
                    }
                }
            }
            fclose(f);
        }
    }

    printf("  ------------------------------------------------------------------\n\n");
}

static void PrintConfigSummary(const char *jsonPath, const CyborgSignConfig *cfg) {
    SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n  Configuration Summary\n");
    printf("  ------------------------------------------------------------------\n");
    ResetColor();
    printf("  Config File   : %s\n", jsonPath);
    printf("  Title         : %s\n", cfg->title[0]        ? cfg->title        : "(unset)");
    printf("  Subject       : %s\n", cfg->subject[0]      ? cfg->subject      : "(unset)");
    printf("  Timestamp URL : %s\n", cfg->timestampUrl[0] ? cfg->timestampUrl : "(none)");
    printf("  Manifest INI  : %s\n", cfg->certIni[0]      ? cfg->certIni      : "(unset)");
    printf("  CDF Output    : %s\n", cfg->certCdf[0]      ? cfg->certCdf      : "(auto)");
    printf("  Catalog CAT   : %s\n", cfg->certCat[0]      ? cfg->certCat      : "(unset)");
    printf("  PFX Cert      : %s\n", cfg->certName[0]     ? cfg->certName     : "(unset)");
    printf("  Cert Reset    : %s\n", cfg->certReset[0]    ? cfg->certReset    : "no");
    printf("  ------------------------------------------------------------------\n\n");
}

static void PrintUsage(void) {
    PrintBanner();
    printf("Usage:\n");
    printf("  cyborg.exe --config <path_to_json> [--new-cert] [--base-dir <dir>] [--dll <path_to_dll>] [--check-only]\n");
    printf("  cyborg.exe --dll-cli -- --config <path_to_json> [--new-cert]\n\n");
    printf("Options:\n");
    printf("  --config <file>, -c   Path to the JSON signing configuration\n");
    printf("  --new-cert            Force generating a new self-signed PFX certificate\n");
    printf("  --base-dir <dir>      Override base directory for resolving relative paths\n");
    printf("  --dll <path>          Explicit path to cyborg.dll (default: auto-search)\n");
    printf("  --check-only          Validate JSON config and print config + file details\n");
    printf("  --dll-cli             Pass remaining arguments directly to Cyborg_RunCli\n\n");
}

int main(int argc, char **argv) {
    InitConsoleStyle();
    ApplyConsoleIcon();

    const char *dllPath    = NULL;
    const char *jsonPath   = NULL;
    const char *baseDirArg = NULL;
    int forceNewCert       = 0;
    int checkOnly          = 0;
    int useDllCli          = 0;
    int dllCliStartIdx     = 0;

    for (int i = 1; i < argc; i++) {
        if (_strcmpi(argv[i], "--") == 0) {
            if (useDllCli) {
                dllCliStartIdx = i + 1;
                break;
            }
        } else if (_strcmpi(argv[i], "--dll-cli") == 0) {
            useDllCli = 1;
            dllCliStartIdx = i + 1;
        } else if (!useDllCli) {
            if ((_strcmpi(argv[i], "--config") == 0 || _strcmpi(argv[i], "-c") == 0) && (i + 1) < argc) {
                jsonPath = argv[++i];
            } else if (_strcmpi(argv[i], "--new-cert") == 0) {
                forceNewCert = 1;
            } else if (_strcmpi(argv[i], "--base-dir") == 0 && (i + 1) < argc) {
                baseDirArg = argv[++i];
            } else if (_strcmpi(argv[i], "--dll") == 0 && (i + 1) < argc) {
                dllPath = argv[++i];
            } else if (_strcmpi(argv[i], "--check-only") == 0) {
                checkOnly = 1;
            } else if (_strcmpi(argv[i], "--help") == 0 || _strcmpi(argv[i], "-h") == 0) {
                PrintUsage();
                return 0;
            }
        }
    }

    PrintBanner();

    CyborgDllApi api;
    if (!LoadCyborgDll(dllPath, &api)) {
        return 1;
    }

    int exitCode = 1;

    if (useDllCli) {
        int subArgc = argc - dllCliStartIdx + 1;
        char **subArgv = (char **)calloc((size_t)subArgc, sizeof(char *));
        if (!subArgv) {
            LogTag("ERROR", FOREGROUND_RED | FOREGROUND_INTENSITY,
                   "Out of memory building DLL CLI arguments.");
            UnloadCyborgDll(&api);
            return 1;
        }
        subArgv[0] = argv[0];
        for (int j = 1; j < subArgc; j++) {
            subArgv[j] = argv[dllCliStartIdx + j - 1];
        }
        LogTag("INFO", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Delegating %d argument(s) to Cyborg_RunCli...", subArgc - 1);
        exitCode = api.RunCli(subArgc, subArgv);
        free(subArgv);
        UnloadCyborgDll(&api);
        if (exitCode == 0) {
            LogTag("SUCCESS", FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Cyborg_RunCli completed cleanly.");
        } else {
            LogTag("ERROR", FOREGROUND_RED | FOREGROUND_INTENSITY, "Cyborg_RunCli exited with code %d.", exitCode);
        }
        return exitCode;
    }

    if (!jsonPath) {
        LogTag("WARN", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "No --config JSON file specified.");
        PrintUsage();
        UnloadCyborgDll(&api);
        return 1;
    }

    CyborgSignConfig cfg;
    LogTag("INFO", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
           "Loading config: %s", jsonPath);
    if (!api.LoadConfigFromJson(jsonPath, &cfg)) {
        LogTag("ERROR", FOREGROUND_RED | FOREGROUND_INTENSITY,
               "Failed to load or parse config from %s", jsonPath);
        UnloadCyborgDll(&api);
        return 1;
    }

    PrintConfigSummary(jsonPath, &cfg);
    DiscoverAndPrintFiles(jsonPath, &cfg, baseDirArg);

    if (checkOnly) {
        LogTag("OK", FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Config validated successfully (--check-only).");
        UnloadCyborgDll(&api);
        return 0;
    }

    if (baseDirArg) {
        char resolvedBase[CYBORG_MAX_STR];
        ExtractDirWithSlash(baseDirArg, resolvedBase, sizeof(resolvedBase));
        if (resolvedBase[0] == '\0') {
            sprintf_s(resolvedBase, sizeof(resolvedBase), "%s\\", baseDirArg);
        }
        LogTag("INFO", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Starting signing pipeline (baseDir=%s, forceNewCert=%d)...",
               resolvedBase, forceNewCert);
        exitCode = api.SignFromConfig(&cfg, resolvedBase, forceNewCert) ? 0 : 1;
    } else {
        LogTag("INFO", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Starting signing pipeline from config: %s (forceNewCert=%d)",
               jsonPath, forceNewCert);
        exitCode = api.SignFromJson(jsonPath, forceNewCert) ? 0 : 1;
    }

    if (exitCode == 0) {
        LogTag("SUCCESS", FOREGROUND_GREEN | FOREGROUND_INTENSITY,
               "Signing pipeline finished successfully.");
        DiscoverAndPrintFiles(jsonPath, &cfg, baseDirArg);
    } else {
        LogTag("ERROR", FOREGROUND_RED | FOREGROUND_INTENSITY,
               "Signing pipeline failed (exit code %d).", exitCode);
    }

    UnloadCyborgDll(&api);
    return exitCode;
}