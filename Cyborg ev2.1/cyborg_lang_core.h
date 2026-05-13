/* ------------------------------------------------------------
   FILE: cyborg_lang_core.h
   PURPOSE: Core language structures for Cyborg→Human conversion.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_CORE_H_
#define _CYBORG_LANG_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* ------------------------------------------------------------
   LANGUAGE TOKEN TYPES
   ------------------------------------------------------------ */

typedef enum _CY_LANG_TOKEN_TYPE {

    CY_LANG_TOK_NONE = 0,
    CY_LANG_TOK_WORD,
    CY_LANG_TOK_NUMBER,
    CY_LANG_TOK_SYMBOL,
    CY_LANG_TOK_NEWLINE,
    CY_LANG_TOK_EOF

} CY_LANG_TOKEN_TYPE;

/* ------------------------------------------------------------
   LANGUAGE TOKEN STRUCTURE
   ------------------------------------------------------------ */

typedef struct _CY_LANG_TOKEN {
    CY_LANG_TOKEN_TYPE type;
    char               text[128];
    int                line;
    int                column;
} CY_LANG_TOKEN;

/* ------------------------------------------------------------
   LANGUAGE STREAM
   ------------------------------------------------------------ */

typedef struct _CY_LANG_STREAM {
    const char *input;
    size_t      pos;
    int         line;
    int         column;
} CY_LANG_STREAM;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

void cy_lang_stream_init(CY_LANG_STREAM *s, const char *input);
CY_LANG_TOKEN cy_lang_next(CY_LANG_STREAM *s);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_CORE_H_ */
