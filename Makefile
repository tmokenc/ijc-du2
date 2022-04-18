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
	
wordcount: wordcount.c io.o libhtab.a
	gcc $(C_FLAGS) -static -o $@ $^

wordcount-: wordcount-.cc
	g++ $(CPP_FLAGS) -O2 -o $@ 
	
io.o: io.c io.h 
	gcc $(C_FLAGS) -c -o $@ $<
	
# Build htab library

# static build
libhtab.a: htab_hash_function.o htab_init.o htab_free.o htab_clear.o htab_resize.o htab_size.o htab_bucket_count.o htab_lookup_add.o htab_for_each.o
	ar -rcs $@ $^

htab_hash_function.o: htab_hash_function.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_init.o: htab_init.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_free.o: htab_free.c htab_private.h
	gcc $(C_FLAGS) -c $<   
htab_clear.o: htab_clear.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_resize.o: htab_resize.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_size.o: htab_size.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_bucket_count.o: htab_bucket_count.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_lookup_add.o: htab_lookup_add.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_for_each.o: htab_for_each.c htab_private.h
	gcc $(C_FLAGS) -c $<

# dynamic