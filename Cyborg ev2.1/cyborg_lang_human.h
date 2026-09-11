/* ------------------------------------------------------------
   FILE: cyborg_lang_human.h
   PURPOSE: Human-readable conversion layer for EV2.1 patches.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_HUMAN_H_
#define _CYBORG_LANG_HUMAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_core.h"
#include <stddef.h>

/* ------------------------------------------------------------
   HUMAN OUTPUT STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_HUMAN_OUTPUT {
    char  *buffer;
    size_t length;
    size_t capacity;
} CY_HUMAN_OUTPUT;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

void cy_human_init(CY_HUMAN_OUTPUT *out);
void cy_human_free(CY_HUMAN_OUTPUT *out);

void cy_human_append(CY_HUMAN_OUTPUT *out, const char *text);
void cy_human_convert_stream(CY_LANG_STREAM *stream,
                             CY_HUMAN_OUTPUT *out);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_HUMAN_H_ */
