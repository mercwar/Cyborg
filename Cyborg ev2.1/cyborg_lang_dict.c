/* ------------------------------------------------------------
   FILE: cyborg_lang_dict.c
   PURPOSE: Cyborg→Human dictionary mapping implementation.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_dict.h"
#include <string.h>

/* ------------------------------------------------------------
   STATIC DICTIONARY TABLE
   ------------------------------------------------------------ */

static CY_DICT_ENTRY _cy_dict_table[] = {

    { "MZ-PATCH",   "Patch Header" },
    { "TARGET",     "Target" },
    { "MODE",       "Mode" },
    { "ARCH",       "Architecture" },
    { "VERSION",    "Version" },

    { "ASM",        "Assembly" },
    { "C",          "C Code" },
    { "LLM-HEX",    "LLM Metadata" },
    { "BIND",       "Binding" },

    { "FUNC",       "Function" },
    { "HOOK",       "Hook" },
    { "MODEL",      "Model" },
    { "FORMAT",     "Format" },

    { NULL, NULL }
};

/* ------------------------------------------------------------
   LOOKUP WORD
   ------------------------------------------------------------ */

const char *cy_dict_lookup(const char *cy_word)
{
    for (size_t i = 0; _cy_dict_table[i].cyborg_word; i++) {
        if (strcmp(_cy_dict_table[i].cyborg_word, cy_word) == 0)
            return _cy_dict_table[i].human_word;
    }
    return NULL;
}

/* ------------------------------------------------------------
   COUNT ENTRIES
   ------------------------------------------------------------ */

size_t cy_dict_count(void)
{
    size_t count = 0;
    while (_cy_dict_table[count].cyborg_word)
        count++;
    return count;
}
