/* ------------------------------------------------------------
   FILE: cyborg_lang_translate.c
   PURPOSE: Semantic translation for Cyborg→Human output.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_translate.h"
#include <string.h>

/* ------------------------------------------------------------
   STATIC TRANSLATION TABLE
   ------------------------------------------------------------ */

static CY_TRANSLATION_ENTRY _cy_trans_table[] = {

    { "MZ-PATCH",      "Patch Header" },
    { "TARGET",        "Target Binary" },
    { "MODE",          "Execution Mode" },
    { "ARCH",          "Architecture" },
    { "VERSION",       "Patch Version" },

    { "ASM",           "Assembly Block" },
    { "C",             "C Function Block" },
    { "LLM-HEX",       "LLM Metadata Block" },
    { "BIND",          "Binding Section" },

    { NULL, NULL }
};

/* ------------------------------------------------------------
   APPLY TRANSLATION TABLE TO OUTPUT
   ------------------------------------------------------------ */

void cy_translate_apply(CY_HUMAN_OUTPUT *out)
{
    for (size_t i = 0; _cy_trans_table[i].cyborg_term; i++) {

        const char *src = _cy_trans_table[i].cyborg_term;
        const char *dst = _cy_trans_table[i].human_term;

        char *pos = strstr(out->buffer, src);
        while (pos) {

            size_t src_len = strlen(src);
            size_t dst_len = strlen(dst);

            if (dst_len > src_len) {
                size_t diff = dst_len - src_len;
                out->capacity += diff + 32;
                out->buffer = (char *)realloc(out->buffer, out->capacity);
            }

            memmove(pos + dst_len, pos + src_len,
                    strlen(pos + src_len) + 1);

            memcpy(pos, dst, dst_len);

            pos = strstr(pos + dst_len, src);
        }
    }
}
