CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable

all: test.o
	$(CC) $(FLAGS) test.o -o main

test.o: test.cpp allocator.hpp
	$(CC) $(FLAGS) test.cpp -c

clean:
	rm -f *.o main
