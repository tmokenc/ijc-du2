/**
 * htab_resize.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

// clean up the htab without free its data
// `t` here is always valid, don't need to check for null pointer
void htab_destroy(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr_ptr[i] == NULL) {
            continue;
        }
        
        struct htab_item *ptr = t->arr_ptr[i];
        while (ptr != NULL) {
            struct htab_item *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    
    free(t->arr_ptr);
    free(t);
}

void htab_resize(htab_t *t, size_t newn) {
    if (t == NULL || newn == 0) {
        return;
    }
    
    htab_t *new_htab = htab_init(newn);
    if (new_htab == NULL) return;
    
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr_ptr[i] == NULL) {
            continue;
        }
        
        struct htab_item *ptr = t->arr_ptr[i];
        
        while (ptr != NULL) {
            size_t nidx = htab_hash_function(ptr->pair->key) % newn;
            struct htab_item *item = malloc(sizeof(struct htab_item));
            
            if (item == NULL) {
                htab_destroy(new_htab);
                return;
            }
            
            item->pair = ptr->pair;
            item->next = NULL;
            
            if (new_htab->arr_ptr[nidx] == NULL) {
                new_htab->arr_ptr[nidx] = item;
            } else {
                struct htab_item *n = new_htab->arr_ptr[nidx];
                
                while (n->next != NULL) {
                    n = n->next;
                }
                
                n->next = item;
            }
            
            ptr = ptr->next;
        }
    }
    
    new_htab->size = t->size;
    htab_destroy(t);
    t = new_htab;
}
