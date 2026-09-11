/* ------------------------------------------------------------
   FILE: cyborg_lang_semantics.c
   PURPOSE: Semantic interpretation for EV2.1 language.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_lang_semantics.h"
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------
   INTERNAL HELPERS
   ------------------------------------------------------------ */

static CY_SEM_NODE *cy_new_sem(CY_SEM_TYPE type, const char *text)
{
    CY_SEM_NODE *n = (CY_SEM_NODE *)malloc(sizeof(CY_SEM_NODE));
    memset(n, 0, sizeof(CY_SEM_NODE));
    n->type = type;
    if (text)
        strncpy(n->text, text, sizeof(n->text) - 1);
    return n;
}

static void cy_sem_add_child(CY_SEM_NODE *parent, CY_SEM_NODE *child)
{
    parent->children = (CY_SEM_NODE **)realloc(
        parent->children,
        sizeof(CY_SEM_NODE *) * (parent->child_count + 1)
    );
    parent->children[parent->child_count++] = child;
}

/* ------------------------------------------------------------
   SYNTAX → SEMANTICS
   ------------------------------------------------------------ */

CY_SEM_NODE *cy_sem_analyze(CY_SYNTAX_NODE *syntax)
{
    if (!syntax)
        return NULL;

    CY_SEM_NODE *root = cy_new_sem(CY_SEM_BLOCK, "ROOT");

    for (size_t i = 0; i < syntax->child_count; i++) {

        CY_SYNTAX_NODE *s = syntax->children[i];
        CY_SEM_TYPE t = CY_SEM_UNKNOWN;

        switch (s->type) {
        case CY_SYNTAX_DIRECTIVE:  t = CY_SEM_HEADER;     break;
        case CY_SYNTAX_FIELD:      t = CY_SEM_FIELD;      break;
        case CY_SYNTAX_BLOCK:      t = CY_SEM_BLOCK;      break;
        case CY_SYNTAX_STATEMENT:  t = CY_SEM_STATEMENT;  break;
        case CY_SYNTAX_LITERAL:    t = CY_SEM_LITERAL;    break;
        case CY_SYNTAX_IDENTIFIER: t = CY_SEM_IDENTIFIER; break;
        default:                   t = CY_SEM_UNKNOWN;    break;
        }

        CY_SEM_NODE *n = cy_new_sem(t, s->text);
        cy_sem_add_child(root, n);
    }

    return root;
}

/* ------------------------------------------------------------
   FREE SEMANTIC TREE
   ------------------------------------------------------------ */

void cy_sem_free(CY_SEM_NODE *node)
{
    if (!node)
        return;

    for (size_t i = 0; i < node->child_count; i++)
        cy_sem_free(node->children[i]);

    if (node->children)
        free(node->children);

    free(node);
}
