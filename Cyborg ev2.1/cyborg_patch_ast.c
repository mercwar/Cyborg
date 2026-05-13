/* ------------------------------------------------------------
   FILE: cyborg_patch_ast.c
   PURPOSE: AST implementation for Cyborg ev2.1 patch language.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_patch_ast.h"
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------
   INTERNAL HELPERS
   ------------------------------------------------------------ */

static void cy_ast_free_node(CY_AST_NODE *node);

/* ------------------------------------------------------------
   AST NODE CREATION
   ------------------------------------------------------------ */

CY_AST_NODE *cy_ast_create(CY_AST_TYPE type, const char *text, int line, int column)
{
    CY_AST_NODE *node = (CY_AST_NODE *)malloc(sizeof(CY_AST_NODE));
    if (!node)
        return NULL;

    memset(node, 0, sizeof(CY_AST_NODE));

    node->type   = type;
    node->line   = line;
    node->column = column;

    if (text)
        strncpy(node->text, text, sizeof(node->text) - 1);

    return node;
}

/* ------------------------------------------------------------
   ADD CHILD NODE
   ------------------------------------------------------------ */

void cy_ast_add_child(CY_AST_NODE *parent, CY_AST_NODE *child)
{
    if (!parent || !child)
        return;

    parent->children = (CY_AST_NODE **)realloc(
        parent->children,
        sizeof(CY_AST_NODE *) * (parent->child_count + 1)
    );

    parent->children[parent->child_count++] = child;
}

/* ------------------------------------------------------------
   FREE AST
   ------------------------------------------------------------ */

void cy_ast_free(CY_AST *ast)
{
    if (!ast || !ast->root)
        return;

    cy_ast_free_node(ast->root);
    ast->root = NULL;
}

/* ------------------------------------------------------------
   FREE AST NODE (RECURSIVE)
   ------------------------------------------------------------ */

static void cy_ast_free_node(CY_AST_NODE *node)
{
    if (!node)
        return;

    for (size_t i = 0; i < node->child_count; i++)
        cy_ast_free_node(node->children[i]);

    if (node->children)
        free(node->children);

    free(node);
}

