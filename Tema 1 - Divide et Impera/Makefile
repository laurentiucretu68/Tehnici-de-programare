all: build run memcheck

build: mainV1.c
	gcc -o mainV1 mainV1.c

run: mainV1
	./mainV1

memcheck: mainV1
	valgrind -v ./mainV1
