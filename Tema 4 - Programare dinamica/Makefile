all: build run memcheck

build: main.c
	gcc -g -O0 -Wall -Wextra -pedantic main.c -o main

run: main
	./main

memcheck: main
	valgrind -v --leak-check=full --show-leak-kinds=all  --track-origins=yes --error-exitcode=1  ./main
