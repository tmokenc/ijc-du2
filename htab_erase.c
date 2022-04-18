/**
 * htab_erase.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */

#include <string.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"
 
bool htab_erase(htab_t * t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return false;
    }
    
    size_t idx = htab_hash_function(key) % t->arr_size;
    struct htab_item *ptr = t->arr_ptr[idx];
    
    while (ptr != NULL) {
        if (strcmp(key, ptr->pair->key) == 0) {
            struct htab_item *to_free = ptr;
            ptr.next = to_free->next;
            free(to_free->pair->key);
            free(to_free->pair);
            free(to_free);
            return true;
        }
        
        ptr = ptr->next;
    }
    
    return false;
}
