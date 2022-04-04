/**
 * io.c
 * Řešení IJC-DU2, 3. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */
 
#include <stdlib.h>
#include <ctype.h>
 
#include "io.h"

int get_word(char *s, int max, FILE *f) {
    if (s == NULL || f == NULL) return EOF;
    if (max == 1) s[0] = '\0';
    if (max <= 1) return 0;

    int c;
    int i = 0;

    // skip all the whitespace at the start
    do {
        c = fgetc(f);
        if (c == EOF) return EOF;
    } while(isspace(c));

    // read the data stream until it got whitespace/EOF or reached the limit
    do {
        s[i++] = c;
        c = fgetc(f);
        
        if (isspace(c) || c == EOF) {
            s[i] = '\0';
            return i;
        }
    } while (i < max - 1);

    // the code here only execute if the word is longer than the `max-1` value
    
    s[i] = '\0';

    while(!isspace(c = fgetc(f)) && c != EOF) {}
    
    return i;
}