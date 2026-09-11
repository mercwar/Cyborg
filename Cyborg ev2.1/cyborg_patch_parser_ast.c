/* ------------------------------------------------------------
   FILE: cyborg_patch_parser_ast.c
   PURPOSE: Parser-to-AST builder for Cyborg ev2.1 patch files.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_patch_parser_ast.h"
#include "cyborg_patch_ast.h"
#include "cyborg_patch_tokens.h"
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------
   INTERNAL STATE
   ------------------------------------------------------------ */

static CY_TOKEN current_token;
static CY_TOKEN (*next_token_fn)(void);

/* ------------------------------------------------------------
   FORWARD DECLARATIONS
   ------------------------------------------------------------ */

static CY_AST_NODE *parse_header(void);
static CY_AST_NODE *parse_asm_block(void);
static CY_AST_NODE *parse_c_block(void);
static CY_AST_NODE *parse_llm_block(void);
static CY_AST_NODE *parse_bind_block(void);

static void advance(void);
static int  match(CY_TOKEN_TYPE type);

/* ------------------------------------------------------------
   ENTRY POINT
   ------------------------------------------------------------ */

CY_AST *cy_parse_to_ast(CY_TOKEN (*next_fn)(void))
{
    next_token_fn = next_fn;
    advance();

    CY_AST *ast = (CY_AST *)malloc(sizeof(CY_AST));
    if (!ast)
        return NULL;

    ast->root = cy_ast_create(CY_AST_HEADER, "ROOT", 0, 0);

    while (current_token.type != CY_TOK_EOF) {

        CY_AST_NODE *node = NULL;

        switch (current_token.type) {

        case CY_TOK_MZ_PATCH:
            node = parse_header();
            break;

        case CY_TOK_ASM:
            node = parse_asm_block();
            break;

        case CY_TOK_CBLOCK:
            node = parse_c_block();
            break;

        case CY_TOK_LLMHEX:
            node = parse_llm_block();
            break;

        case CY_TOK_BIND:
            node = parse_bind_block();
            break;

        default:
            advance();
            continue;
        }

        if (node)
            cy_ast_add_child(ast->root, node);
    }

    return ast;
}

/* ------------------------------------------------------------
   HEADER PARSER
   ------------------------------------------------------------ */

static CY_AST_NODE *parse_header(void)
{
    CY_AST_NODE *node = cy_ast_create(CY_AST_HEADER, "HEADER",
                                      current_token.line, current_token.column);

    advance(); /* MZ-PATCH */

    while (current_token.type != CY_TOK_ASM &&
           current_token.type != CY_TOK_CBLOCK &&
           current_token.type != CY_TOK_LLMHEX &&
           current_token.type != CY_TOK_BIND &&
           current_token.type != CY_TOK_EOF) {

        CY_AST_NODE *field = cy_ast_create(CY_AST_HEADER,
                                           current_token.text,
                                           current_token.line,
                                           current_token.column);

        cy_ast_add_child(node, field);
        advance();
    }

    return node;
}

/* ------------------------------------------------------------
   ASM BLOCK PARSER
   ------------------------------------------------------------ */

static CY_AST_NODE *parse_asm_block(void)
{
    CY_AST_NODE *node = cy_ast_create(CY_AST_ASM_BLOCK,
                                      current_token.text,
                                      current_token.line,
                                      current_token.column);

    advance(); /* [ASM...] */

    while (current_token.type != CY_TOK_ENDASM &&
           current_token.type != CY_TOK_EOF) {

        CY_AST_NODE *child = cy_ast_create(CY_AST_ASM_INSTRUCTION,
                                           current_token.text,
                                           current_token.line,
                                           current_token.column);

        cy_ast_add_child(node, child);
        advance();
    }

    if (current_token.type == CY_TOK_ENDASM)
        advance();

    return node;
}

/* ------------------------------------------------------------
   C BLOCK PARSER
   ------------------------------------------------------------ */

static CY_AST_NODE *parse_c_block(void)
{
    CY_AST_NODE *node = cy_ast_create(CY_AST_C_BLOCK,
                                      "[C]",
                                      current_token.line,
                                      current_token.column);

    advance(); /* [C] */

    while (current_token.type != CY_TOK_ASM &&
           current_token.type != CY_TOK_LLMHEX &&
           current_token.type != CY_TOK_BIND &&
           current_token.type != CY_TOK_EOF) {

        CY_AST_NODE *func = cy_ast_create(CY_AST_C_FUNCTION,
                                          current_token.text,
                                          current_token.line,
                                          current_token.column);

        cy_ast_add_child(node, func);
        advance();
    }

    return node;
}

/* ------------------------------------------------------------
   LLM BLOCK PARSER
   ------------------------------------------------------------ */

static CY_AST_NODE *parse_llm_block(void)
{
    CY_AST_NODE *node = cy_ast_create(CY_AST_LLM_BLOCK,
                                      "[LLM-HEX]",
                                      current_token.line,
                                      current_token.column);

    advance(); /* [LLM-HEX] */

    while (current_token.type != CY_TOK_BIND &&
           current_token.type != CY_TOK_ASM &&
           current_token.type != CY_TOK_CBLOCK &&
           current_token.type != CY_TOK_EOF) {

        CY_AST_NODE *child = cy_ast_create(CY_AST_LLM_DATA,
                                           current_token.text,
                                           current_token.line,
                                           current_token.column);

        cy_ast_add_child(node, child);
        advance();
    }

    return node;
}

/* ------------------------------------------------------------
   BIND BLOCK PARSER
   ------------------------------------------------------------ */

static CY_AST_NODE *parse_bind_block(void)
{
    CY_AST_NODE *node = cy_ast_create(CY_AST_BIND_BLOCK,
                                      "[BIND]",
                                      current_token.line,
                                      current_token.column);

    advance(); /* [BIND] */

    while (current_token.type != CY_TOK_ASM &&
           current_token.type != CY_TOK_CBLOCK &&
           current_token.type != CY_TOK_LLMHEX &&
           current_token.type != CY_TOK_EOF) {

        CY_AST_NODE *entry = cy_ast_create(CY_AST_BIND_ENTRY,
                                           current_token.text,
                                           current_token.line,
                                           current_token.column);

        cy_ast_add_child(node, entry);
        advance();
    }

    return node;
}

/* ------------------------------------------------------------
   TOKEN CONTROL
   ------------------------------------------------------------ */

static void advance(void)
{
    current_token = next_token_fn();
}

static int match(CY_TOKEN_TYPE type)
{
    if (current_token.type == type) {
        advance();
        return 1;
    }
    return 0;
}

