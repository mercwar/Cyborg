/* ------------------------------------------------------------
   FILE: cyborg_lang_meta.c
   PURPOSE: Meta-language classification for EV2.1 patches.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_meta.h"
#include <string.h>

/* ------------------------------------------------------------
   META TABLE
   ------------------------------------------------------------ */

static CY_META_DESC _cy_meta_table[] = {

    { "MZ-PATCH",  CY_META_DIRECTIVE,  "Patch header directive" },
    { "TARGET",    CY_META_KEYWORD,    "Target binary field" },
    { "MODE",      CY_META_KEYWORD,    "Execution mode field" },
    { "ARCH",      CY_META_KEYWORD,    "Architecture field" },
    { "VERSION",   CY_META_KEYWORD,    "Patch version field" },

    { "ASM",       CY_META_DIRECTIVE,  "Assembly block" },
    { "C",         CY_META_DIRECTIVE,  "C function block" },
    { "LLM-HEX",   CY_META_DIRECTIVE,  "LLM metadata block" },
    { "BIND",      CY_META_DIRECTIVE,  "Binding section" },

    { NULL,        CY_META_UNKNOWN,    NULL }
};

/* ------------------------------------------------------------
   CLASSIFY TOKEN
   ------------------------------------------------------------ */

CY_META_CATEGORY cy_meta_classify(const char *token)
{
    for (size_t i = 0; _cy_meta_table[i].token; i++) {
        if (strcmp(_cy_meta_table[i].token, token) == 0)
            return _cy_meta_table[i].category;
    }

    if (token[0] >= '0' && token[0] <= '9')
        return CY_META_LITERAL;

    if ((token[0] >= 'A' && token[0] <= 'Z') ||
        (token[0] >= 'a' && token[0] <= 'z'))
        return CY_META_IDENTIFIER;

    return CY_META_UNKNOWN;
}

/* ------------------------------------------------------------
   DESCRIBE TOKEN
   ------------------------------------------------------------ */

const char *cy_meta_describe(const char *token)
{
    for (size_t i = 0; _cy_meta_table[i].token; i++) {
        if (strcmp(_cy_meta_table[i].token, token) == 0)
            return _cy_meta_table[i].description;
    }

    return "Unrecognized token";
}
