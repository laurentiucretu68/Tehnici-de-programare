all: build run memcheck

build: main.c
	gcc -o main main.c

run: main
	./main

memcheck: main
	valgrind -v --leak-check=full  ./main
