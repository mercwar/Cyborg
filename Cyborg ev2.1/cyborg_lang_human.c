/* ------------------------------------------------------------
   FILE: cyborg_lang_human.c
   PURPOSE: Human-readable output generator for EV2.1 patches.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_human.h"
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------
   INITIALIZE OUTPUT BUFFER
   ------------------------------------------------------------ */

void cy_human_init(CY_HUMAN_OUTPUT *out)
{
    out->capacity = 1024;
    out->length   = 0;
    out->buffer   = (char *)malloc(out->capacity);
    if (out->buffer)
        out->buffer[0] = '\0';
}

/* ------------------------------------------------------------
   FREE OUTPUT BUFFER
   ------------------------------------------------------------ */

void cy_human_free(CY_HUMAN_OUTPUT *out)
{
    if (out->buffer)
        free(out->buffer);

    out->buffer   = NULL;
    out->length   = 0;
    out->capacity = 0;
}

/* ------------------------------------------------------------
   APPEND TEXT
   ------------------------------------------------------------ */

void cy_human_append(CY_HUMAN_OUTPUT *out, const char *text)
{
    size_t tlen = strlen(text);

    if (out->length + tlen + 1 > out->capacity) {
        out->capacity *= 2;
        out->buffer = (char *)realloc(out->buffer, out->capacity);
    }

    memcpy(out->buffer + out->length, text, tlen);
    out->length += tlen;
    out->buffer[out->length] = '\0';
}

/* ------------------------------------------------------------
   CONVERT TOKEN STREAM → HUMAN TEXT
   ------------------------------------------------------------ */

void cy_human_convert_stream(CY_LANG_STREAM *stream,
                             CY_HUMAN_OUTPUT *out)
{
    CY_LANG_TOKEN tok;

    while (1) {
        tok = cy_lang_next(stream);

        if (tok.type == CY_LANG_TOK_EOF)
            break;

        if (tok.type == CY_LANG_TOK_NEWLINE) {
            cy_human_append(out, "\n");
            continue;
        }

        cy_human_append(out, tok.text);
        cy_human_append(out, " ");
    }
}
