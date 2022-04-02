# Makefile
# Řešení IJC-DU2, 2. 4. 2022
# Autor: tmokenc, FIT
#
# Pozamky: Makefile to build the programs

C_FLAGS = -std=c11 -pedantic -Wall -Wextra
CPP_FLAGS = -std=c++17 -pedantic -Wall

all: tail

tail: tail.c
	gcc $(C_FLAGS) -o tail tail.c