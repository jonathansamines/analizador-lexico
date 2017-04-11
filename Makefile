## Utilidades de compilación

all: build run

build:
	gcc src/main.c -o main.out

run:
	./main.out
