/* ------------------------------------------------------------
   FILE: cyborg_lang_syntax.c
   PURPOSE: Syntax tree builder for EV2.1 language.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_syntax.h"
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------
   INTERNAL HELPERS
   ------------------------------------------------------------ */

static CY_SYNTAX_NODE *cy_new_node(CY_SYNTAX_NODE_TYPE type,
                                   const char *text)
{
    CY_SYNTAX_NODE *n = (CY_SYNTAX_NODE *)malloc(sizeof(CY_SYNTAX_NODE));
    memset(n, 0, sizeof(CY_SYNTAX_NODE));
    n->type = type;
    if (text)
        strncpy(n->text, text, sizeof(n->text) - 1);
    return n;
}

static void cy_add_child(CY_SYNTAX_NODE *parent, CY_SYNTAX_NODE *child)
{
    parent->children = (CY_SYNTAX_NODE **)realloc(
        parent->children,
        sizeof(CY_SYNTAX_NODE *) * (parent->child_count + 1)
    );
    parent->children[parent->child_count++] = child;
}

/* ------------------------------------------------------------
   PARSE STREAM → SYNTAX TREE
   ------------------------------------------------------------ */

CY_SYNTAX_NODE *cy_syntax_parse(CY_LANG_STREAM *stream)
{
    CY_SYNTAX_NODE *root = cy_new_node(CY_SYNTAX_BLOCK, "ROOT");

    CY_LANG_TOKEN tok;
    while (1) {

        tok = cy_lang_next(stream);
        if (tok.type == CY_LANG_TOK_EOF)
            break;

        if (tok.type == CY_LANG_TOK_NEWLINE)
            continue;

        const CY_GRAMMAR_RULE *rule = cy_grammar_match(tok.text);

        if (rule) {
            CY_SYNTAX_NODE *n = cy_new_node(
                (CY_SYNTAX_NODE_TYPE)rule->type,
                tok.text
            );
            cy_add_child(root, n);
        } else {
            CY_SYNTAX_NODE *n = cy_new_node(CY_SYNTAX_IDENTIFIER, tok.text);
            cy_add_child(root, n);
        }
    }

    return root;
}

/* ------------------------------------------------------------
   FREE SYNTAX TREE
   ------------------------------------------------------------ */

void cy_syntax_free(CY_SYNTAX_NODE *node)
{
    if (!node)
        return;

    for (size_t i = 0; i < node->child_count; i++)
        cy_syntax_free(node->children[i]);

    if (node->children)
        free(node->children);

    free(node);
}
