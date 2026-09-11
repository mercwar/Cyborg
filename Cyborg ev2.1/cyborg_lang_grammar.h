/* ------------------------------------------------------------
   FILE: cyborg_lang_grammar.h
   PURPOSE: Grammar rules for Cyborg→Human language conversion.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_GRAMMAR_H_
#define _CYBORG_LANG_GRAMMAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_core.h"
#include "cyborg_lang_meta.h"

/* ------------------------------------------------------------
   GRAMMAR RULE TYPES
   ------------------------------------------------------------ */

typedef enum _CY_GRAMMAR_RULE_TYPE {

    CY_RULE_UNKNOWN = 0,
    CY_RULE_STATEMENT,
    CY_RULE_ASSIGNMENT,
    CY_RULE_DIRECTIVE,
    CY_RULE_BLOCK,
    CY_RULE_FIELD

} CY_GRAMMAR_RULE_TYPE;

/* ------------------------------------------------------------
   GRAMMAR RULE STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_GRAMMAR_RULE {
    CY_GRAMMAR_RULE_TYPE type;
    const char          *pattern;
    const char          *description;
} CY_GRAMMAR_RULE;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

const CY_GRAMMAR_RULE *cy_grammar_match(const char *token);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_GRAMMAR_H_ */
