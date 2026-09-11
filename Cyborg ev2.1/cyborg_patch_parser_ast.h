/* ------------------------------------------------------------
   FILE: cyborg_patch_parser_ast.h
   PURPOSE: Header for Parser-to-AST builder for Cyborg ev2.1.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_PARSER_AST_H_
#define _CYBORG_PATCH_PARSER_AST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_patch_ast.h"
#include "cyborg_patch_tokens.h"

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

/*
 * FUNCTION: cy_parse_to_ast
 * PURPOSE:  Converts a token stream into an AST.
 * PARAMS:   next_fn - function pointer returning next CY_TOKEN.
 * RETURNS:  Pointer to CY_AST on success, NULL on failure.
 */
CY_AST *cy_parse_to_ast(CY_TOKEN (*next_fn)(void));

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_PARSER_AST_H_ */
