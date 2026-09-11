/* ------------------------------------------------------------
   FILE: cyborg_patch_tokens.h
   PURPOSE: Token definitions for Cyborg ev2.1 patch lexer.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_TOKENS_H_
#define _CYBORG_PATCH_TOKENS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------
   TOKEN ENUMERATION
   ------------------------------------------------------------ */

typedef enum _CY_TOKEN_TYPE {

    /* End of file */
    CY_TOK_EOF = 0,

    /* Identifiers */
    CY_TOK_IDENTIFIER,
    CY_TOK_LABEL,

    /* Literals */
    CY_TOK_HEXVALUE,
    CY_TOK_STRING,

    /* Keywords */
    CY_TOK_MZ_PATCH,
    CY_TOK_TARGET,
    CY_TOK_MODE,
    CY_TOK_ARCH,
    CY_TOK_VERSION,

    CY_TOK_ASM,
    CY_TOK_ENDASM,
    CY_TOK_HOOK,
    CY_TOK_AT,
    CY_TOK_ORG,

    CY_TOK_CBLOCK,      /* [C] */

    CY_TOK_LLMHEX,      /* [LLM-HEX] */
    CY_TOK_FORMAT,
    CY_TOK_MODEL,
    CY_TOK_LLM_MODE,
    CY_TOK_SIZE,
    CY_TOK_DATA,
    CY_TOK_ENDDATA,

    CY_TOK_BIND,
    CY_TOK_BIND_ASM,
    CY_TOK_BIND_C,
    CY_TOK_BIND_LLM,
    CY_TOK_BIND_MODE,

    /* Symbols */
    CY_TOK_COLON,
    CY_TOK_COMMA,
    CY_TOK_LBRACE,
    CY_TOK_RBRACE,
    CY_TOK_LPAREN,
    CY_TOK_RPAREN,

    /* Assembly mnemonics */
    CY_TOK_MOV,
    CY_TOK_PUSH,
    CY_TOK_POP,
    CY_TOK_CALL,
    CY_TOK_JMP,
    CY_TOK_CMP,
    CY_TOK_TEST,
    CY_TOK_RET,
    CY_TOK_NOP,

    /* Registers */
    CY_TOK_REG_AX,
    CY_TOK_REG_BX,
    CY_TOK_REG_CX,
    CY_TOK_REG_DX,
    CY_TOK_REG_SP,
    CY_TOK_REG_BP,
    CY_TOK_REG_SI,
    CY_TOK_REG_DI,

    /* ABI keywords */
    CY_TOK_STDCALL,
    CY_TOK_FASTCALL,
    CY_TOK_THISCALL,
    CY_TOK_CYCALL

} CY_TOKEN_TYPE;

/* ------------------------------------------------------------
   TOKEN STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_TOKEN {
    CY_TOKEN_TYPE type;
    char          text[512];
    int           line;
    int           column;
} CY_TOKEN;

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_TOKENS_H_ */
