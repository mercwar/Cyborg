/* ------------------------------------------------------------
   FILE: cyborg_lang_semantics.h
   PURPOSE: Semantic interpretation for Cyborg→Human language.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_SEMANTICS_H_
#define _CYBORG_LANG_SEMANTICS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_syntax.h"
#include "cyborg_lang_human.h"

/* ------------------------------------------------------------
   SEMANTIC NODE TYPES
   ------------------------------------------------------------ */

typedef enum _CY_SEM_TYPE {

    CY_SEM_UNKNOWN = 0,
    CY_SEM_HEADER,
    CY_SEM_FIELD,
    CY_SEM_BLOCK,
    CY_SEM_STATEMENT,
    CY_SEM_LITERAL,
    CY_SEM_IDENTIFIER

} CY_SEM_TYPE;

/* ------------------------------------------------------------
   SEMANTIC NODE STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_SEM_NODE {
    CY_SEM_TYPE type;
    char        text[128];
    struct _CY_SEM_NODE **children;
    size_t      child_count;
} CY_SEM_NODE;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

CY_SEM_NODE *cy_sem_analyze(CY_SYNTAX_NODE *syntax);
void cy_sem_free(CY_SEM_NODE *node);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_SEMANTICS_H_ */
