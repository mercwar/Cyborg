#ifndef CYBORG_H
#define CYBORG_H

#include <windows.h>
#include <stddef.h>

#ifdef CYBORG_EXPORTS
  #define CYBORG_API __declspec(dllexport)
#elif defined(CYBORG_IMPORT)
  #define CYBORG_API __declspec(dllimport)
#else
  #define CYBORG_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CYBORG_MAX_STR   512
#define CYBORG_MAX_FILES 100

typedef struct {
    char title[CYBORG_MAX_STR];
    char timestampUrl[CYBORG_MAX_STR];
    char certCat[CYBORG_MAX_STR];
    char certIni[CYBORG_MAX_STR];
    char certCdf[CYBORG_MAX_STR];
    char certReset[32];
    char certName[CYBORG_MAX_STR];
    char subject[CYBORG_MAX_STR];
    char password[CYBORG_MAX_STR];
} CyborgSignConfig;

CYBORG_API int  __stdcall Cyborg_LoadConfigFromJson(const char *jsonPath, CyborgSignConfig *outCfg);
CYBORG_API int  __stdcall Cyborg_SignFromConfig(const CyborgSignConfig *cfg, const char *baseDir, int forceNewCert);
CYBORG_API int  __stdcall Cyborg_SignFromJson(const char *jsonPath, int forceNewCertOverride);
CYBORG_API int  __stdcall Cyborg_RunCli(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* CYBORG_H */
