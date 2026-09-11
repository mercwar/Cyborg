/* ------------------------------------------------------------
   FILE: cyborg_lang_core.c
   PURPOSE: Core tokenizer for Cyborg→Human language conversion.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_core.h"
#include <ctype.h>
#include <string.h>

/* ------------------------------------------------------------
   INITIALIZE STREAM
   ------------------------------------------------------------ */

void cy_lang_stream_init(CY_LANG_STREAM *s, const char *input)
{
    s->input  = input;
    s->pos    = 0;
    s->line   = 1;
    s->column = 1;
}

/* ------------------------------------------------------------
   NEXT TOKEN
   ------------------------------------------------------------ */

CY_LANG_TOKEN cy_lang_next(CY_LANG_STREAM *s)
{
    CY_LANG_TOKEN tok;
    memset(&tok, 0, sizeof(tok));

    const char *p = s->input + s->pos;

    /* Skip whitespace */
    while (*p == ' ' || *p == '\t') {
        p++;
        s->pos++;
        s->column++;
    }

    /* Newline */
    if (*p == '\n') {
        tok.type = CY_LANG_TOK_NEWLINE;
        strcpy(tok.text, "\\n");
        tok.line   = s->line;
        tok.column = s->column;

        s->pos++;
        s->line++;
        s->column = 1;

        return tok;
    }

    /* EOF */
    if (*p == '\0') {
        tok.type = CY_LANG_TOK_EOF;
        strcpy(tok.text, "<EOF>");
        tok.line   = s->line;
        tok.column = s->column;
        return tok;
    }

    /* Number */
    if (isdigit(*p)) {
        tok.type = CY_LANG_TOK_NUMBER;
        tok.line = s->line;
        tok.column = s->column;

        size_t i = 0;
        while (isdigit(*p) && i < sizeof(tok.text) - 1) {
            tok.text[i++] = *p;
            p++;
            s->pos++;
            s->column++;
        }
        tok.text[i] = '\0';
        return tok;
    }

    /* Word */
    if (isalpha(*p)) {
        tok.type = CY_LANG_TOK_WORD;
        tok.line = s->line;
        tok.column = s->column;

        size_t i = 0;
        while ((isalnum(*p) || *p == '_') && i < sizeof(tok.text) - 1) {
            tok.text[i++] = *p;
            p++;
            s->pos++;
            s->column++;
        }
        tok.text[i] = '\0';
        return tok;
    }

    /* Symbol */
    tok.type = CY_LANG_TOK_SYMBOL;
    tok.text[0] = *p;
    tok.text[1] = '\0';
    tok.line   = s->line;
    tok.column = s->column;

    s->pos++;
    s->column++;

    return tok;
}
