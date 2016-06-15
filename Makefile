CC=mpicc

all: src/main.c
	$(CC) src/*.c -o main

clean:
	rm -rf main
