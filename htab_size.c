/**
 * htab_size.c
 * Řešení IJC-DU2, 15. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
size_t htab_size(const htab_t * t) {
    return t == NULL ? 0 : t->size;
}