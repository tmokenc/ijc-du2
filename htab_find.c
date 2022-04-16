/**
 * htab_find.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */

#include "htab.h"
#include "htab_private.h"
 
htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }
    
    size_t idx = htab_hash_function(key) % t->arr_size;
    struct htab_item *ptr = t->arr_ptr[idx];
    
    while (ptr != NULL) {
        if (strcmp(key, ptr->pair->key) == 0) {
            return ptr->pair;
        }
        
        ptr = ptr->next;
    }
    
    return NULL;
}