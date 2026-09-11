/* ------------------------------------------------------------
   FILE: cyborg_lang_grammar.c
   PURPOSE: Grammar rule matching for EV2.1 language.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_grammar.h"
#include <string.h>

/* ------------------------------------------------------------
   GRAMMAR TABLE
   ------------------------------------------------------------ */

static CY_GRAMMAR_RULE _cy_grammar_table[] = {

    { CY_RULE_DIRECTIVE, "MZ-PATCH", "Patch header directive" },
    { CY_RULE_FIELD,     "TARGET",   "Target field" },
    { CY_RULE_FIELD,     "MODE",     "Mode field" },
    { CY_RULE_FIELD,     "ARCH",     "Architecture field" },
    { CY_RULE_FIELD,     "VERSION",  "Version field" },

    { CY_RULE_BLOCK,     "ASM",      "Assembly block" },
    { CY_RULE_BLOCK,     "C",        "C code block" },
    { CY_RULE_BLOCK,     "LLM-HEX",  "LLM metadata block" },
    { CY_RULE_BLOCK,     "BIND",     "Binding block" },

    { CY_RULE_STATEMENT, "FUNC",     "Function declaration" },
    { CY_RULE_STATEMENT, "HOOK",     "Hook declaration" },

    { CY_RULE_UNKNOWN,   NULL,       NULL }
};

/* ------------------------------------------------------------
   MATCH GRAMMAR RULE
   ------------------------------------------------------------ */

const CY_GRAMMAR_RULE *cy_grammar_match(const char *token)
{
    for (size_t i = 0; _cy_grammar_table[i].pattern; i++) {
        if (strcmp(_cy_grammar_table[i].pattern, token) == 0)
            return &_cy_grammar_table[i];
    }
    return NULL;
}
