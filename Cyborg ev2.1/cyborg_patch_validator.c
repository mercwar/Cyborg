/* ------------------------------------------------------------
   FILE: cyborg_patch_validator.c
   PURPOSE: Validation implementation for Cyborg ev2.1 patches.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#include "cyborg_patch_validator.h"
#include <string.h>
#include <stdlib.h>

/* ------------------------------------------------------------
   INTERNAL HELPERS
   ------------------------------------------------------------ */

static int validate_header(const CY_AST_NODE *node,
                           CY_VALIDATION_REPORT *report);

static int validate_asm(const CY_AST_NODE *node,
                        CY_VALIDATION_REPORT *report);

static int validate_cblock(const CY_AST_NODE *node,
                           CY_VALIDATION_REPORT *report);

static int validate_llm(const CY_AST_NODE *node,
                        CY_VALIDATION_REPORT *report);

static int validate_bind(const CY_AST_NODE *node,
                         CY_VALIDATION_REPORT *report);

/* ------------------------------------------------------------
   MAIN VALIDATION ENTRY
   ------------------------------------------------------------ */

CY_VALIDATION_RESULT cy_validate_ast(const CY_AST *ast,
                                     CY_VALIDATION_REPORT *report)
{
    if (!ast || !ast->root) {
        report->result = CY_VALIDATE_ERR_UNKNOWN;
        strcpy(report->message, "AST is null.");
        return report->result;
    }

    for (size_t i = 0; i < ast->root->child_count; i++) {

        const CY_AST_NODE *node = ast->root->children[i];

        switch (node->type) {

        case CY_AST_HEADER:
            if (!validate_header(node, report))
                return report->result;
            break;

        case CY_AST_ASM_BLOCK:
            if (!validate_asm(node, report))
                return report->result;
            break;

        case CY_AST_C_BLOCK:
            if (!validate_cblock(node, report))
                return report->result;
            break;

        case CY_AST_LLM_BLOCK:
            if (!validate_llm(node, report))
                return report->result;
            break;

        case CY_AST_BIND_BLOCK:
            if (!validate_bind(node, report))
                return report->result;
            break;

        default:
            break;
        }
    }

    report->result = CY_VALIDATE_OK;
    strcpy(report->message, "Validation successful.");
    return CY_VALIDATE_OK;
}

/* ------------------------------------------------------------
   HEADER VALIDATION
   ------------------------------------------------------------ */

static int validate_header(const CY_AST_NODE *node,
                           CY_VALIDATION_REPORT *report)
{
    int has_target = 0;
    int has_mode   = 0;
    int has_arch   = 0;
    int has_ver    = 0;

    for (size_t i = 0; i < node->child_count; i++) {

        const char *t = node->children[i]->text;

        if (strncmp(t, "TARGET:", 7) == 0) has_target = 1;
        else if (strncmp(t, "MODE:", 5) == 0) has_mode = 1;
        else if (strncmp(t, "ARCH:", 5) == 0) has_arch = 1;
        else if (strncmp(t, "VERSION:", 8) == 0) has_ver = 1;
    }

    if (!has_target) {
        report->result = CY_VALIDATE_ERR_TARGET_INVALID;
        strcpy(report->message, "Missing TARGET field.");
        return 0;
    }

    if (!has_mode) {
        report->result = CY_VALIDATE_ERR_MODE_INVALID;
        strcpy(report->message, "Missing MODE field.");
        return 0;
    }

    if (!has_arch) {
        report->result = CY_VALIDATE_ERR_ARCH_INVALID;
        strcpy(report->message, "Missing ARCH field.");
        return 0;
    }

    if (!has_ver) {
        report->result = CY_VALIDATE_ERR_VERSION_MISMATCH;
        strcpy(report->message, "Missing VERSION field.");
        return 0;
    }

    return 1;
}

/* ------------------------------------------------------------
   ASM VALIDATION
   ------------------------------------------------------------ */

static int validate_asm(const CY_AST_NODE *node,
                        CY_VALIDATION_REPORT *report)
{
    if (node->child_count == 0) {
        report->result = CY_VALIDATE_ERR_ASM_EMPTY;
        strcpy(report->message, "ASM block is empty.");
        return 0;
    }

    for (size_t i = 0; i < node->child_count; i++) {

        const char *t = node->children[i]->text;

        if (strcmp(t, "HLT") == 0 ||
            strcmp(t, "CLI") == 0 ||
            strcmp(t, "STI") == 0) {

            report->result = CY_VALIDATE_ERR_ASM_UNSAFE_INSTRUCTION;
            strcpy(report->message, "Unsafe instruction detected.");
            return 0;
        }
    }

    return 1;
}

/* ------------------------------------------------------------
   C BLOCK VALIDATION
   ------------------------------------------------------------ */

static int validate_cblock(const CY_AST_NODE *node,
                           CY_VALIDATION_REPORT *report)
{
    if (node->child_count == 0) {
        report->result = CY_VALIDATE_ERR_CBLOCK_EMPTY;
        strcpy(report->message, "C block contains no functions.");
        return 0;
    }

    int has_abi = 0;

    for (size_t i = 0; i < node->child_count; i++) {

        const char *t = node->children[i]->text;

        if (strstr(t, "__stdcall") ||
            strstr(t, "__fastcall") ||
            strstr(t, "__thiscall") ||
            strstr(t, "__cycall")) {

            has_abi = 1;
        }
    }

    if (!has_abi) {
        report->result = CY_VALIDATE_ERR_CFUNC_ABI_MISSING;
        strcpy(report->message, "C function missing ABI.");
        return 0;
    }

    return 1;
}

/* ------------------------------------------------------------
   LLM BLOCK VALIDATION
   ------------------------------------------------------------ */

static int validate_llm(const CY_AST_NODE *node,
                        CY_VALIDATION_REPORT *report)
{
    int has_format = 0;
    int has_model  = 0;

    for (size_t i = 0; i < node->child_count; i++) {

        const char *t = node->children[i]->text;

        if (strncmp(t, "FORMAT:", 7) == 0) has_format = 1;
        else if (strncmp(t, "MODEL:", 6) == 0) has_model = 1;
    }

    if (!has_format) {
        report->result = CY_VALIDATE_ERR_LLM_FORMAT_INVALID;
        strcpy(report->message, "LLM block missing FORMAT.");
        return 0;
    }

    if (!has_model) {
        report->result = CY_VALIDATE_ERR_LLM_MODEL_MISSING;
        strcpy(report->message, "LLM block missing MODEL.");
        return 0;
    }

    return 1;
}

/* ------------------------------------------------------------
   BIND BLOCK VALIDATION
   ------------------------------------------------------------ */

static int validate_bind(const CY_AST_NODE *node,
                         CY_VALIDATION_REPORT *report)
{
    int has_asm = 0;
    int has_c   = 0;

    for (size_t i = 0; i < node->child_count; i++) {

        const char *t = node->children[i]->text;

        if (strncmp(t, "ASM:", 4) == 0) has_asm = 1;
        else if (strncmp(t, "C:", 2) == 0) has_c = 1;
    }

    if (!has_asm) {
        report->result = CY_VALIDATE_ERR_BIND_ASM_NOT_FOUND;
        strcpy(report->message, "BIND missing ASM reference.");
        return 0;
    }

    if (!has_c) {
        report->result = CY_VALIDATE_ERR_BIND_CFUNC_NOT_FOUND;
        strcpy(report->message, "BIND missing C function reference.");
        return 0;
    }

    return 1;
}

