// [AVIS-AI-SCAN] FILE: memory_sandbox.c | CLASS: MEMORY_ISOLATION | TARGET: WIN64_UCRT
#include "cyborg_core.h"

LPVOID AllocateIsolatedBlock(SIZE_T size) {
    printf("[MEMORY SANDBOX]: Requesting virtual allocation block size: %zu bytes.\n", size);
    LPVOID allocated_ptr = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!allocated_ptr) {
        printf("[MEMORY SANDBOX CRITICAL]: VirtualAlloc failed to lock page layout boundaries.\n");
        return NULL;
    }
    printf("[MEMORY SANDBOX]: Dynamic allocation locked at structural mapping address: %p\n", allocated_ptr);
    return allocated_ptr;
}
