# Makefile
# Řešení IJC-DU2, 2. 4. 2022
# Autor: tmokenc, FIT
#
# Pozamky: Makefile to build the programs

C_FLAGS = -std=c11 -pedantic -Wall -Wextra
CPP_FLAGS = -std=c++17 -pedantic -Wall

all: tail wordcount

tail: tail.c
	gcc $(C_FLAGS) -o $@ $<
	
wordcount: wordcount.c io.o
	gcc $(C_FLAGS) -o $@ $?

wordcount-: wordcount-.cc
	g++ $(CPP_FLAGS) -O2 -o $@ 
	
io.o: io.c io.h 
	gcc $(C_FLAGS) -c -o $@ $<