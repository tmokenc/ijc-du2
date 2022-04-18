/**
 * wordcount.c
 * Řešení IJC-DU2, 16. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdio.h>
#include "io.h"
#include "htab.h"

/*
The size of htab
Assuming that the program runs on a 64bit environment and its L1 cache is >32KiB
The pointer on 64bit system is 8 bytes wide
4000 pointers will make up 32000 bytes, plus the size of its arr_size and size
the htab can easily fit in the L1 cache of the CPU, means less cache miss
thus make it faster to access its data,
its not always the case but I think it's better for the htab to have an oppotunity to be in the L1 cache
*/
#define SIZE 4000
#define WORD_LEN 127

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
