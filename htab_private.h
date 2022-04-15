/**
 * htab_private.h
 * Řešení IJC-DU2, 13. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */

#ifndef __HTABLE_PRIVATE_H__
#define __HTABLE_PRIVATE_H__

#include "htab.h"

struct htab {
    size_t size; // aktuální počet záznamů [(key,data),next]
    size_t arr_size; // velikost pole ukazatelů (počet položek)
    struct arr_ptr *array[]; // ukazatel na dynamicky alokované pole ukazatelů
};

struct htab_item {
    char *key; // Klic daneho zaznamu.
    int data; // Pocet zaznamu vazajicich se k danemu klici.
    struct htab_item *next; // Ukazatel na dalsi polozku seznamu.
};

#endif