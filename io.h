/**
 * io.h
 * Řešení IJC-DU2, 2. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 */

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

/*
čte jedno slovo ze souboru f do zadaného pole znaků
a vrátí délku slova (z delších slov načte prvních max-1 znaků,
a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.
*/
int get_word(char *s, int max, FILE *f);

#endif