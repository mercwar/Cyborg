/* ------------------------------------------------------------
   FILE: cyborg_lang_phrases.h
   PURPOSE: Phrase generator for Cyborg→Human language output.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_PHRASES_H_
#define _CYBORG_LANG_PHRASES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_semantics.h"
#include "cyborg_lang_human.h"

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

void cy_phrase_generate(CY_SEM_NODE *sem, CY_HUMAN_OUTPUT *out);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_PHRASES_H_ */
