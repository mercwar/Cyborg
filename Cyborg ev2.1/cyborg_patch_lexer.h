/* ------------------------------------------------------------
   FILE: cyborg_patch_lexer.h
   PURPOSE: Header for Cyborg ev2.1 patch lexer.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_LEXER_H_
#define _CYBORG_PATCH_LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_patch_tokens.h"

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

/*
 * FUNCTION: cy_lex_init
 * PURPOSE:  Initializes the lexer with a text buffer.
 * PARAMS:   buffer - pointer to null-terminated patch text.
 * RETURNS:  None.
 */
void cy_lex_init(const char *buffer);

/*
 * FUNCTION: cy_lex_next
 * PURPOSE:  Retrieves the next token from the input stream.
 * RETURNS:  CY_TOKEN structure containing token type and text.
 */
CY_TOKEN cy_lex_next(void);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_LEXER_H_ */
