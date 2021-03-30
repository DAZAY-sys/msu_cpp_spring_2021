CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable

all: main

main: test.o allocator.o
	$(CC) $(FLAGS) test.o allocator.o -o main

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) allocator.cpp -c

test.o: test.cpp allocator.hpp
	$(CC) $(FLAGS) test.cpp -c

test: main
	./main

clean:
	rm -f *.o main
