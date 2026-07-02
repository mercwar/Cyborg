// [AVIS-AI-SCAN] FILE: avis_scanner.c | CLASS: REPO_SCANNER | TARGET: WIN64_UCRT
#include "cyborg_core.h"
#include "constellation_map.h"

void ScanLocalArtifacts(const char* target_path) {
    printf("[AVIS SCANNER]: Activating File Scanner under targeted path: %s\n", target_path);
    char search_pattern[MAX_PATH_LEN];
    snprintf(search_pattern, sizeof(search_pattern), "%s\\*", target_path);

    WIN32_FIND_DATAA find_data;
    HANDLE find_handle = FindFirstFileA(search_pattern, &find_data);

    if (find_handle == INVALID_HANDLE_VALUE) {
        printf("[AVIS SCANNER ERROR]: Target path lookups aborted.\n");
        return;
    }

    do {
        if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            printf("[AVIS SCANNER]: Discovered Artifact Target: %s\n", find_data.cFileName);
            RegisterIngestArtifact(find_data.cFileName);
        }
    } while (FindNextFileA(find_handle, &find_data));

    FindClose(find_handle);
    printf("[AVIS SCANNER]: Structural scanning loop successfully concluded.\n");
}
