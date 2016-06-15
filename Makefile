MPICPPC=mpic++

all: src/main.cpp
	$(MPICPPC) src/*.cpp -o main

clean:
	rm -rf main
