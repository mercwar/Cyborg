/* ------------------------------------------------------------
   FILE: cyborg_lang_meta.h
   PURPOSE: Meta-language descriptors for Cyborg→Human conversion.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_META_H_
#define _CYBORG_LANG_META_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_lang_core.h"

/* ------------------------------------------------------------
   META TOKEN CATEGORY
   ------------------------------------------------------------ */

typedef enum _CY_META_CATEGORY {

    CY_META_UNKNOWN = 0,
    CY_META_KEYWORD,
    CY_META_DIRECTIVE,
    CY_META_IDENTIFIER,
    CY_META_LITERAL,
    CY_META_OPERATOR,
    CY_META_STRUCTURE

} CY_META_CATEGORY;

/* ------------------------------------------------------------
   META TOKEN DESCRIPTOR
   ------------------------------------------------------------ */

typedef struct _CY_META_DESC {
    const char      *token;
    CY_META_CATEGORY category;
    const char      *description;
} CY_META_DESC;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

CY_META_CATEGORY cy_meta_classify(const char *token);
const char *cy_meta_describe(const char *token);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_META_H_ */
