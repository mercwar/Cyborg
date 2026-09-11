/* ------------------------------------------------------------
   FILE: cyborg_patch_ast.h
   PURPOSE: Abstract Syntax Tree definitions for Cyborg ev2.1.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_AST_H_
#define _CYBORG_PATCH_AST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* ------------------------------------------------------------
   AST NODE TYPES
   ------------------------------------------------------------ */

typedef enum _CY_AST_TYPE {

    CY_AST_NONE = 0,

    /* Header */
    CY_AST_HEADER,

    /* ASM */
    CY_AST_ASM_BLOCK,
    CY_AST_ASM_INSTRUCTION,
    CY_AST_ASM_HOOK,
    CY_AST_ASM_ORG,

    /* C */
    CY_AST_C_BLOCK,
    CY_AST_C_FUNCTION,

    /* LLM */
    CY_AST_LLM_BLOCK,
    CY_AST_LLM_DATA,

    /* BIND */
    CY_AST_BIND_BLOCK,
    CY_AST_BIND_ENTRY

} CY_AST_TYPE;

/* ------------------------------------------------------------
   AST NODE STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_AST_NODE {
    CY_AST_TYPE        type;
    char               text[512];
    struct _CY_AST_NODE **children;
    size_t             child_count;
    int                line;
    int                column;
} CY_AST_NODE;

/* ------------------------------------------------------------
   AST ROOT STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_AST {
    CY_AST_NODE *root;
} CY_AST;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

/*
 * FUNCTION: cy_ast_create
 * PURPOSE:  Allocates a new AST node.
 * RETURNS:  Pointer to CY_AST_NODE.
 */
CY_AST_NODE *cy_ast_create(CY_AST_TYPE type, const char *text, int line, int column);

/*
 * FUNCTION: cy_ast_add_child
 * PURPOSE:  Appends a child node to a parent node.
 * RETURNS:  None.
 */
void cy_ast_add_child(CY_AST_NODE *parent, CY_AST_NODE *child);

/*
 * FUNCTION: cy_ast_free
 * PURPOSE:  Frees an AST and all child nodes.
 * RETURNS:  None.
 */
void cy_ast_free(CY_AST *ast);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_AST_H_ */
