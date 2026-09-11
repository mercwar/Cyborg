// [AVIS-AI-SCAN] FILE: error_handler.c | CLASS: METRIC_LOGGER | TARGET: WIN64_UCRT
#include "cyborg_core.h"

void LogAvisError(int error_code, const char* message) {
    fprintf(stderr, "[AVIS ERROR LOG][CODE: 0x%X]: %s\n", error_code, message);
}
