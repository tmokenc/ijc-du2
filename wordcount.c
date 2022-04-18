/**
 * wordcount.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdio.h>
#include "io.h"
#include "htab.h"

// The size of htab
#define SIZE 3000
#define WORD_LEN 100

void print_data(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main() {
    htab_t *t = htab_init(SIZE);
    char buf[WORD_LEN + 1];
    
    if (t == NULL) {
        return 1;
    }
    
    while (get_word(buf, WORD_LEN, stdin) != EOF) {
        if (htab_lookup_add(t, buf) == NULL) {
            htab_free(t);
            return 1;
        }
    }
    
    htab_for_each(t, print_data);
    
    return 0;
}