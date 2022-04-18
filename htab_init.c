/**
 * htab_init.c
 * Řešení IJC-DU2, 3. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n) {
    if (n == 0) {
        fprintf(stderr, "n have to be at least 1");
        return NULL;
    }
    
    htab_t *data = malloc(sizeof(htab_t));
    
    if (data == NULL) {
        fprintf(stderr, "Out Of Memory");
        return NULL;
    }
    
    data->size = 0;
    data->arr_size = n;
    data->arr_ptr = malloc(sizeof(struct htab_item *) * n);
    
    if (data->arr_ptr == NULL) {
        fprintf(stderr, "Out Of Memory");
        free(data);
        return NULL;
    }
    
    for (size_t i = 0; i < n; i++) {
        data->arr_ptr[i] = NULL;
    }
    
    return data;
}
