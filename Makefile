# Makefile
# Řešení IJC-DU2, 2. 4. 2022
# Autor: tmokenc, FIT
#
# Pozamky: Makefile to build the programs

C_FLAGS = -std=c11 -pedantic -Wall -Wextra
CPP_FLAGS = -std=c++17 -pedantic -Wall

all: tail wordcount- wordcount

tail: tail.c
	gcc $(C_FLAGS) -o tail tail.c
	
wordcount: wordcount.c
	gcc $(C_FLAGS) -o wordcount wordcount.c

wordcount-: wordcount-.cc
	g++ $(CPP_FLAGS) -O2 -o wordcount- wordcount-.cc
	
io.o: io.h io.c
	gcc $(C_FLAGS) -c -o io.o io.c