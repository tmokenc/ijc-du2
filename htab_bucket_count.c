/**
 * htab_bucket_count.c
 * Řešení IJC-DU2, 15. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include "htab.h"
#include "htab_private.h"
 
size_t htab_bucket_count(const htab_t * t) {
    return t == NULL ? 0 : t->arr_size;
}
