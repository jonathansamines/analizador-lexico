## Utilidades de compilación

all: clean build run

build:
	@gcc src/main.c -o main.out

run:
	@./main.out

clean:
	@rm main.out | exit 0
