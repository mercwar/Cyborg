/* ------------------------------------------------------------
   FILE: cyborg_patch_validator.h
   PURPOSE: Validation interface for Cyborg ev2.1 patch files.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_VALIDATOR_H_
#define _CYBORG_PATCH_VALIDATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_patch_ast.h"

/* ------------------------------------------------------------
   VALIDATION RESULT ENUM
   ------------------------------------------------------------ */

typedef enum _CY_VALIDATION_RESULT {

    CY_VALIDATE_OK = 0,

    /* Header errors */
    CY_VALIDATE_ERR_HEADER_MISSING,
    CY_VALIDATE_ERR_TARGET_INVALID,
    CY_VALIDATE_ERR_MODE_INVALID,
    CY_VALIDATE_ERR_ARCH_INVALID,
    CY_VALIDATE_ERR_VERSION_MISMATCH,

    /* ASM errors */
    CY_VALIDATE_ERR_ASM_EMPTY,
    CY_VALIDATE_ERR_ASM_INVALID_INSTRUCTION,
    CY_VALIDATE_ERR_ASM_UNSAFE_INSTRUCTION,
    CY_VALIDATE_ERR_ASM_INVALID_HOOK,

    /* C block errors */
    CY_VALIDATE_ERR_CBLOCK_EMPTY,
    CY_VALIDATE_ERR_CFUNC_INVALID,
    CY_VALIDATE_ERR_CFUNC_ABI_MISSING,

    /* LLM block errors */
    CY_VALIDATE_ERR_LLM_FORMAT_INVALID,
    CY_VALIDATE_ERR_LLM_MODEL_MISSING,
    CY_VALIDATE_ERR_LLM_MODE_INVALID,
    CY_VALIDATE_ERR_LLM_DATA_INVALID,

    /* BIND errors */
    CY_VALIDATE_ERR_BIND_ASM_NOT_FOUND,
    CY_VALIDATE_ERR_BIND_CFUNC_NOT_FOUND,
    CY_VALIDATE_ERR_BIND_MODE_INVALID,

    /* Generic */
    CY_VALIDATE_ERR_UNKNOWN

} CY_VALIDATION_RESULT;

/* ------------------------------------------------------------
   VALIDATION REPORT STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_VALIDATION_REPORT {
    CY_VALIDATION_RESULT result;
    char                 message[512];
    int                  line;
    int                  column;
} CY_VALIDATION_REPORT;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

/*
 * FUNCTION: cy_validate_ast
 * PURPOSE:  Validates a Cyborg ev2.1 AST.
 * PARAMS:   ast - pointer to AST structure.
 *           report - pointer to validation report structure.
 * RETURNS:  CY_VALIDATE_OK on success, error code on failure.
 */
CY_VALIDATION_RESULT cy_validate_ast(const CY_AST *ast,
                                     CY_VALIDATION_REPORT *report);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_VALIDATOR_H_ */
