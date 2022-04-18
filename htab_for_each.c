/**
 * htab_for_each.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */

#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    if (t == NULL) {
        return;
    }
    
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *ptr = t->arr_ptr[i];
        
        if (ptr == NULL) {
            continue;
        }
        
        while (ptr != NULL) {
            (*f)(ptr->pair);
            ptr = ptr->next;
        }
    }
}