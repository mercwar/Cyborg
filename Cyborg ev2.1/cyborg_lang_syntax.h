/* ------------------------------------------------------------
   FILE: cyborg_lang_syntax.h
   PURPOSE: Syntax rules for Cyborg→Human language conversion.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_SYNTAX_H_
#define _CYBORG_LANG_SYNTAX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_core.h"
#include "cyborg_lang_grammar.h"

/* ------------------------------------------------------------
   SYNTAX NODE TYPES
   ------------------------------------------------------------ */

typedef enum _CY_SYNTAX_NODE_TYPE {

    CY_SYNTAX_UNKNOWN = 0,
    CY_SYNTAX_STATEMENT,
    CY_SYNTAX_FIELD,
    CY_SYNTAX_BLOCK,
    CY_SYNTAX_DIRECTIVE,
    CY_SYNTAX_LITERAL,
    CY_SYNTAX_IDENTIFIER

} CY_SYNTAX_NODE_TYPE;

/* ------------------------------------------------------------
   SYNTAX NODE STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_SYNTAX_NODE {
    CY_SYNTAX_NODE_TYPE type;
    char                text[128];
    struct _CY_SYNTAX_NODE **children;
    size_t              child_count;
} CY_SYNTAX_NODE;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

CY_SYNTAX_NODE *cy_syntax_parse(CY_LANG_STREAM *stream);
void cy_syntax_free(CY_SYNTAX_NODE *node);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_SYNTAX_H_ */
