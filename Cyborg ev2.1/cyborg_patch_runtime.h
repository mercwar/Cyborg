/* ------------------------------------------------------------
   FILE: cyborg_patch_runtime.h
   PURPOSE: Runtime execution interface for Cyborg ev2.1 patches.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_RUNTIME_H_
#define _CYBORG_PATCH_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cyborg_patch_ast.h"
#include <stddef.h>

/* ------------------------------------------------------------
   RUNTIME RESULT ENUM
   ------------------------------------------------------------ */

typedef enum _CY_RUNTIME_RESULT {

    CY_RUNTIME_OK = 0,

    /* Load errors */
    CY_RUNTIME_ERR_LOAD_FAILED,
    CY_RUNTIME_ERR_INVALID_FORMAT,
    CY_RUNTIME_ERR_UNSUPPORTED_ARCH,

    /* Execution errors */
    CY_RUNTIME_ERR_ASM_EXECUTION_FAILED,
    CY_RUNTIME_ERR_CFUNC_NOT_FOUND,
    CY_RUNTIME_ERR_LLM_MODEL_FAILURE,
    CY_RUNTIME_ERR_BINDING_FAILURE,

    /* Generic */
    CY_RUNTIME_ERR_UNKNOWN

} CY_RUNTIME_RESULT;

/* ------------------------------------------------------------
   RUNTIME CONTEXT
   ------------------------------------------------------------ */

typedef struct _CY_RUNTIME_CONTEXT {
    void   *target_image;
    size_t  image_size;
    void   *llm_context;
    void   *cfunc_table;
} CY_RUNTIME_CONTEXT;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

/*
 * FUNCTION: cy_runtime_init
 * PURPOSE:  Initializes a runtime context for patch execution.
 * RETURNS:  CY_RUNTIME_OK on success.
 */
CY_RUNTIME_RESULT cy_runtime_init(CY_RUNTIME_CONTEXT *ctx,
                                  const char *target_path);

/*
 * FUNCTION: cy_runtime_apply
 * PURPOSE:  Applies an EV2.1 patch AST to the runtime context.
 * RETURNS:  CY_RUNTIME_OK on success.
 */
CY_RUNTIME_RESULT cy_runtime_apply(CY_RUNTIME_CONTEXT *ctx,
                                   const CY_AST *ast);

/*
 * FUNCTION: cy_runtime_execute
 * PURPOSE:  Executes all bound ASM/C/LLM operations.
 * RETURNS:  CY_RUNTIME_OK on success.
 */
CY_RUNTIME_RESULT cy_runtime_execute(CY_RUNTIME_CONTEXT *ctx);

/*
 * FUNCTION: cy_runtime_free
 * PURPOSE:  Releases all runtime resources.
 * RETURNS:  None.
 */
void cy_runtime_free(CY_RUNTIME_CONTEXT *ctx);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_RUNTIME_H_ */
