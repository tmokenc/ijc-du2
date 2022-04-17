/**
 * htab_lookup_add.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

char *allocate_string(const char *str) {
    char *dst = malloc(strlen(str) + 1);
    if (dst == NULL) return NULL;        
    strcpy(dst, str);                    
    return dst;    
}
struct htab_item *create_item(htab_key_t k) {
    char *key = allocate_string(k);
    htab_pair_t *pair = malloc(sizeof(htab_pair_t));
    struct htab_item *item = malloc(sizeof(struct htab_item));
    if (pair == NULL || key == NULL || item == NULL) {
        free(key);
        free(pair);
        free(item);
        return NULL;
    }
    
    pair->key = key;
    pair->value = 1;
    item->pair = pair;
    item->next = NULL;
    
    return item;
}

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        fprintf(stderr, "The htab or key is NULL");
        return NULL;
    }
    
    size_t idx = htab_hash_function(key) % t->arr_size;
    
    if (t->arr_ptr[idx] == NULL) {
        t->arr_ptr[idx] = create_item(key);
        if (t->arr_ptr[idx] == NULL) {
            fprintf(stderr, "Out Of Memory");
            return NULL;
        }
        
        t->size += 1;
        return t->arr_ptr[idx]->pair;
    }
    
    struct htab_item *item_ptr = t->arr_ptr[idx];
    
    while (item_ptr->next != NULL) {
        if (strcmp(key, item_ptr->pair->key) == 0) {
            item_ptr->pair->value++;
            return item_ptr->pair;
        }
        
        item_ptr = item_ptr->next;
    }
    
    item_ptr = create_item(key);
    
    if (item_ptr == NULL) {
        fprintf(stderr, "Out Of Memory");
        return NULL;
    }
    
    t->size += 1;
    return item_ptr->pair;
}