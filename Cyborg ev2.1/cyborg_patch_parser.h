/* ------------------------------------------------------------
   FILE: cyborg_patch_parser.h
   PURPOSE: Header definitions for Cyborg ev2.1 patch parser.
   VERSION: EV2.1
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_PATCH_PARSER_H_
#define _CYBORG_PATCH_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------
   DATA STRUCTURES
   ------------------------------------------------------------ */

typedef struct _CY_HEADER {
    char target[512];
    char mode[32];
    char arch[32];
    char version[32];
} CY_HEADER;

typedef struct _CY_ASM_BLOCK {
    char   label[128];
    char **lines;
    size_t line_count;
} CY_ASM_BLOCK;

typedef struct _CY_C_BLOCK {
    char   **functions;
    size_t   function_count;
} CY_C_BLOCK;

typedef struct _CY_LLM_BLOCK {
    char   format[32];
    char   model[256];
    char   mode[32];
    char **hex_data;
    size_t hex_count;
} CY_LLM_BLOCK;

typedef struct _CY_BIND_ENTRY {
    char asm_label[128];
    char c_func[128];
    char llm_model[256];
    char bind_mode[32];
} CY_BIND_ENTRY;

typedef struct _CY_PARSER {
    CY_HEADER      header;
    CY_ASM_BLOCK  *asm_blocks;
    size_t         asm_count;
    CY_C_BLOCK     c_block;
    CY_LLM_BLOCK  *llm_blocks;
    size_t         llm_count;
    CY_BIND_ENTRY *bind_entries;
    size_t         bind_count;
} CY_PARSER;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

/*
 * FUNCTION: cy_parse_patch_file
 * PURPOSE:  Parses a Cyborg ev2.1 patch file.
 * RETURNS:  0 on success, non-zero on failure.
 */
int cy_parse_patch_file(const char *path, struct _CY_PARSER *parser);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_PATCH_PARSER_H_ */
