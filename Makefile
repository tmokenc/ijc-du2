# gcc -std=c11 -pedantic -Wall -Wextra priklad1.c
# g++ -std=c++17 -pedantic -Wall priklad.cc

C_FLAGS = -std=c11 -pedantic -Wall -Wextra
CPP_FLAGS = -std=c++17 -pedantic -Wall

all: tail

tail: tail.c
	gcc $(C_FLAGS) -o tail tail.c
