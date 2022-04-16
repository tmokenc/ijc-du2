/**
 * htab_clear.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"
 
void htab_clear(htab_t * t) {
    if (t == NULL) {
        return;
    }
    
    for (size_t i = 0; i < t->arr_size; i++) {
        while (t->arr_ptr[i] != NULL) {
            struct htab_item *ptr = t->arr_ptr[i];
            free(ptr->pair->key);
            free(ptr->pair);
            free(ptr);
            t->arr_ptr[i] = ptr->next;
        }
    }
    
    t->size = 0;
}