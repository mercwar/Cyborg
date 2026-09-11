/* ------------------------------------------------------------
   FILE: cyborg_lang_dict.h
   PURPOSE: Cyborg→Human dictionary mapping for EV2.1 language.
   VERSION: EV2.1-LANG
   AUTHOR: Cyborg Engineering
   ------------------------------------------------------------ */

#ifndef _CYBORG_LANG_DICT_H_
#define _CYBORG_LANG_DICT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* ------------------------------------------------------------
   DICTIONARY ENTRY
   ------------------------------------------------------------ */

typedef struct _CY_DICT_ENTRY {
    const char *cyborg_word;
    const char *human_word;
} CY_DICT_ENTRY;

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */

const char *cy_dict_lookup(const char *cy_word);
size_t cy_dict_count(void);

#ifdef __cplusplus
}
#endif

#endif /* _CYBORG_LANG_DICT_H_ */
