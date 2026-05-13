/* ------------------------------------------------------------
   FILE: cyborg_lang_phrases.c
   PURPOSE: Phrase construction for EV2.1 human-readable output.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_phrases.h"
#include <string.h>

/* ------------------------------------------------------------
   INTERNAL HELPERS
   ------------------------------------------------------------ */

static void cy_phrase_emit(CY_HUMAN_OUTPUT *out,
                           const char *prefix,
                           const char *text)
{
    if (prefix) {
        cy_human_append(out, prefix);
        cy_human_append(out, ": ");
    }
    cy_human_append(out, text);
    cy_human_append(out, "\n");
}

/* ------------------------------------------------------------
   SEMANTICS → PHRASES
   ------------------------------------------------------------ */

void cy_phrase_generate(CY_SEM_NODE *sem, CY_HUMAN_OUTPUT *out)
{
    if (!sem)
        return;

    for (size_t i = 0; i < sem->child_count; i++) {

        CY_SEM_NODE *n = sem->children[i];

        switch (n->type) {

        case CY_SEM_HEADER:
            cy_phrase_emit(out, "Header", n->text);
            break;

        case CY_SEM_FIELD:
            cy_phrase_emit(out, "Field", n->text);
            break;

        case CY_SEM_BLOCK:
            cy_phrase_emit(out, "Block", n->text);
            break;

        case CY_SEM_STATEMENT:
            cy_phrase_emit(out, "Statement", n->text);
            break;

        case CY_SEM_LITERAL:
            cy_phrase_emit(out, "Literal", n->text);
            break;

        case CY_SEM_IDENTIFIER:
            cy_phrase_emit(out, "Identifier", n->text);
            break;

        default:
            cy_phrase_emit(out, "Unknown", n->text);
            break;
        }
    }
}
