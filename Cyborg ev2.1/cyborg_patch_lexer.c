/* ------------------------------------------------------------
   FILE: cyborg_patch_lexer.c
   PURPOSE: Lexer for Cyborg ev2.1 patch files.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_patch_tokens.h"
#include "cyborg_patch_lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ------------------------------------------------------------
   INTERNAL STATE
   ------------------------------------------------------------ */

typedef struct _CY_LEXER {
    const char *text;
    size_t      length;
    size_t      index;
    int         line;
    int         column;
} CY_LEXER;

static CY_LEXER lex;

/* ------------------------------------------------------------
   FORWARD DECLARATIONS
   ------------------------------------------------------------ */

static void cy_lex_advance(void);
static char cy_lex_peek(void);
static void cy_lex_skip_whitespace(void);
static CY_TOKEN cy_lex_identifier(void);
static CY_TOKEN cy_lex_hexvalue(void);
static CY_TOKEN cy_lex_string(void);

/* ------------------------------------------------------------
   INITIALIZATION
   ------------------------------------------------------------ */

void cy_lex_init(const char *buffer)
{
    lex.text   = buffer;
    lex.length = strlen(buffer);
    lex.index  = 0;
    lex.line   = 1;
    lex.column = 1;
}

/* ------------------------------------------------------------
   MAIN LEXER ENTRY
   ------------------------------------------------------------ */

CY_TOKEN cy_lex_next(void)
{
    CY_TOKEN tok;
    memset(&tok, 0, sizeof(tok));

    cy_lex_skip_whitespace();

    if (lex.index >= lex.length) {
        tok.type = CY_TOK_EOF;
        return tok;
    }

    char c = cy_lex_peek();

    /* IDENTIFIER OR KEYWORD */
    if (isalpha(c) || c == '_' || c == '[') {
        tok = cy_lex_identifier();
        return tok;
    }

    /* HEX VALUE */
    if (c == '0' && lex.text[lex.index+1] == 'x') {
        tok = cy_lex_hexvalue();
        return tok;
    }

    /* STRING */
    if (c == '"') {
        tok = cy_lex_string();
        return tok;
    }

    /* SYMBOLS */
    switch (c) {
    case ':': tok.type = CY_TOK_COLON;   strcpy(tok.text, ":"); break;
    case ',': tok.type = CY_TOK_COMMA;   strcpy(tok.text, ","); break;
    case '{': tok.type = CY_TOK_LBRACE;  strcpy(tok.text, "{"); break;
    case '}': tok.type = CY_TOK_RBRACE;  strcpy(tok.text, "}"); break;
    case '(': tok.type = CY_TOK_LPAREN;  strcpy(tok.text, "("); break;
    case ')': tok.type = CY_TOK_RPAREN;  strcpy(tok.text, ")"); break;
    default:
        tok.type = CY_TOK_IDENTIFIER;
        tok.text[0] = c;
        tok.text[1] = 0;
        break;
    }

    cy_lex_advance();
    return tok;
}

/* ------------------------------------------------------------
   INTERNAL HELPERS
   ------------------------------------------------------------ */

static void cy_lex_advance(void)
{
    if (lex.index < lex.length) {
        if (lex.text[lex.index] == '\n') {
            lex.line++;
            lex.column = 1;
        } else {
            lex.column++;
        }
        lex.index++;
    }
}

static char cy_lex_peek(void)
{
    if (lex.index >= lex.length)
        return 0;
    return lex.text[lex.index];
}

static void cy_lex_skip_whitespace(void)
{
    while (lex.index < lex.length) {
        char c = cy_lex_peek();
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            cy_lex_advance();
        else
            break;
    }
}

/* ------------------------------------------------------------
   IDENTIFIER / KEYWORD
   ------------------------------------------------------------ */

static CY_TOKEN cy_lex_identifier(void)
{
    CY_TOKEN tok;
    memset(&tok, 0, sizeof(tok));

    size_t start = lex.index;
    size_t len   = 0;

    while (lex.index < lex.length) {
        char c = cy_lex_peek();
        if (isalnum(c) || c == '_' || c == '-' || c == '[' || c == ']') {
            cy_lex_advance();
            len++;
        } else break;
    }

    strncpy(tok.text, lex.text + start, len);
    tok.text[len] = 0;

    /* KEYWORD MAPPING */
    if (strcmp(tok.text, "MZ-PATCH") == 0) tok.type = CY_TOK_MZ_PATCH;
    else if (strcmp(tok.text, "TARGET:") == 0) tok.type = CY_TOK_TARGET;
    else if (strcmp(tok.text, "MODE:") == 0) tok.type = CY_TOK_MODE;
    else if (strcmp(tok.text, "ARCH:") == 0) tok.type = CY_TOK_ARCH;
    else if (strcmp(tok.text, "VERSION:") == 0) tok.type = CY_TOK_VERSION;

    else if (strcmp(tok.text, "[ASM") == 0) tok.type = CY_TOK_ASM;
    else if (strcmp(tok.text, "ENDASM") == 0) tok.type = CY_TOK_ENDASM;
    else if (strcmp(tok.text, "HOOK") == 0) tok.type = CY_TOK_HOOK;
    else if (strcmp(tok.text, "AT") == 0) tok.type = CY_TOK_AT;
    else if (strcmp(tok.text, "ORG") == 0) tok.type = CY_TOK_ORG;

    else if (strcmp(tok.text, "[C]") == 0) tok.type = CY_TOK_CBLOCK;

    else if (strcmp(tok.text, "[LLM-HEX]") == 0) tok.type = CY_TOK_LLMHEX;
    else if (strcmp(tok.text, "FORMAT:") == 0) tok.type = CY_TOK_FORMAT;
    else if (strcmp(tok.text, "MODEL:") == 0) tok.type = CY_TOK_MODEL;
    else if (strcmp(tok.text, "MODE:") == 0) tok.type = CY_TOK_LLM_MODE;
    else if (strcmp(tok.text, "SIZE:") == 0) tok.type = CY_TOK_SIZE;
    else if (strcmp(tok.text, "DATA:") == 0) tok.type = CY_TOK_DATA;
    else if (strcmp(tok.text, "ENDDATA") == 0) tok.type = CY_TOK_ENDDATA;

    else if (strcmp(tok.text, "[BIND]") == 0) tok.type = CY_TOK_BIND;
    else if (strcmp(tok.text, "ASM:") == 0) tok.type = CY_TOK_BIND_ASM;
    else if (strcmp(tok.text, "C:") == 0) tok.type = CY_TOK_BIND_C;
    else if (strcmp(tok.text, "LLM:") == 0) tok.type = CY_TOK_BIND_LLM;
    else if (strcmp(tok.text, "MODE:") == 0) tok.type = CY_TOK_BIND_MODE;

    /* ASM mnemonics */
    else if (strcmp(tok.text, "MOV") == 0) tok.type = CY_TOK_MOV;
    else if (strcmp(tok.text, "PUSH") == 0) tok.type = CY_TOK_PUSH;
    else if (strcmp(tok.text, "POP") == 0) tok.type = CY_TOK_POP;
    else if (strcmp(tok.text, "CALL") == 0) tok.type = CY_TOK_CALL;
    else if (strcmp(tok.text, "JMP") == 0) tok.type = CY_TOK_JMP;
    else if (strcmp(tok.text, "CMP") == 0) tok.type = CY_TOK_CMP;
    else if (strcmp(tok.text, "TEST") == 0) tok.type = CY_TOK_TEST;
    else if (strcmp(tok.text, "RET") == 0) tok.type = CY_TOK_RET;
    else if (strcmp(tok.text, "NOP") == 0) tok.type = CY_TOK_NOP;

    /* Registers */
    else if (strcmp(tok.text, "AX") == 0) tok.type = CY_TOK_REG_AX;
    else if (strcmp(tok.text, "BX") == 0) tok.type = CY_TOK_REG_BX;
    else if (strcmp(tok.text, "CX") == 0) tok.type = CY_TOK_REG_CX;
    else if (strcmp(tok.text, "DX") == 0) tok.type = CY_TOK_REG_DX;
    else if (strcmp(tok.text, "SP") == 0) tok.type = CY_TOK_REG_SP;
    else if (strcmp(tok.text, "BP") == 0) tok.type = CY_TOK_REG_BP;
    else if (strcmp(tok.text, "SI") == 0) tok.type = CY_TOK_REG_SI;
    else if (strcmp(tok.text, "DI") == 0) tok.type = CY_TOK_REG_DI;

    /* ABI */
    else if (strcmp(tok.text, "__stdcall") == 0) tok.type = CY_TOK_STDCALL;
    else if (strcmp(tok.text, "__fastcall") == 0) tok.type = CY_TOK_FASTCALL;
    else if (strcmp(tok.text, "__thiscall") == 0) tok.type = CY_TOK_THISCALL;
    else if (strcmp(tok.text, "__cycall") == 0) tok.type = CY_TOK_CYCALL;

    else tok.type = CY_TOK_IDENTIFIER;

    tok.line   = lex.line;
    tok.column = lex.column;

    return tok;
}

/* ------------------------------------------------------------
   HEX VALUE
   ------------------------------------------------------------ */

static CY_TOKEN cy_lex_hexvalue(void)
{
    CY_TOKEN tok;
    memset(&tok, 0, sizeof(tok));

    size_t start = lex.index;
    cy_lex_advance(); /* 0 */
    cy_lex_advance(); /* x */

    while (isxdigit(cy_lex_peek()))
        cy_lex_advance();

    size_t len = lex.index - start;
    strncpy(tok.text, lex.text + start, len);
    tok.text[len] = 0;

    tok.type   = CY_TOK_HEXVALUE;
    tok.line   = lex.line;
    tok.column = lex.column;

    return tok;
}

/* ------------------------------------------------------------
   STRING
   ------------------------------------------------------------ */

static CY_TOKEN cy_lex_string(void)
{
    CY_TOKEN tok;
    memset(&tok, 0, sizeof(tok));

    cy_lex_advance(); /* skip " */

    size_t start = lex.index;

    while (cy_lex_peek() != '"' && lex.index < lex.length)
        cy_lex_advance();

    size_t len = lex.index - start;
    strncpy(tok.text, lex.text + start, len);
    tok.text[len] = 0;

    cy_lex_advance(); /* skip closing " */

    tok.type   = CY_TOK_STRING;
    tok.line   = lex.line;
    tok.column = lex.column;

    return tok;
}

