CC=mpicc

all: src/main.c
	$(CC) src/*.c -o main

clean:
	rm -rf main

get-deps:
	sudo apt-get install libcr-dev mpich2 mpich2-doc