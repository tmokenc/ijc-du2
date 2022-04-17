/**
 * htab_free.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdlib.h>
#include "htab.h"
 
void htab_free(htab_t * t) {
    htab_clear(t);
    free(t);
}