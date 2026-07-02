// [AVIS-AI-SCAN] FILE: cyborg_core.h | CLASS: SYS_HEADER | TARGET: WIN64_UCRT
#ifndef CYBORG_CORE_H
#define CYBORG_CORE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PHRASE_LEN 128
#define MAX_PATH_LEN   260

typedef struct {
    char human_phrase[MAX_PHRASE_LEN];
    UINT win_message;
    WPARAM w_param;
    LPARAM l_param;
} CyborgMapping;

extern CyborgMapping CyborgTranslationTable[];
extern size_t CyborgTableSize;

BOOL DispatchBorgVector(HWND target_hwnd, UINT message, WPARAM wp, LPARAM lp);
BOOL ExecuteCyborgTranslation(const char* human_input, HWND target_hwnd);

#endif // CYBORG_CORE_H
