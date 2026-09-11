/* ------------------------------------------------------------
   FILE: cyborg_lang_translate.h
   PURPOSE: Translation layer for Cyborg→Human semantic mapping.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_TRANSLATE_H_
#define _CYBORG_LANG_TRANSLATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_core.h"
#include "cyborg_lang_human.h"

/* ------------------------------------------------------------
   TRANSLATION ENTRY
   ------------------------------------------------------------ */

typedef struct _CY_TRANSLATION_ENTRY {
    const char *cyborg_term;
    const char *human_term;
} CY_TRANSLATION_ENTRY;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

void cy_translate_apply(CY_HUMAN_OUTPUT *out);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_TRANSLATE_H_ */
