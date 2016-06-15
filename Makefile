MPICPPC=mpicxx

all: src/main.cc
	$(MPICPPC) src/*.cc -o main

clean:
	rm -rf main
