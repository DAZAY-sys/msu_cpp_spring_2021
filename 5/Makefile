CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable

all: main

main: test.o
	$(CC) $(FLAGS) test.o -o main

test.o: test.cpp serializer.hpp serializer.tpp
	$(CC) $(FLAGS) test.cpp -c

test: main
	./main

clean:
	rm -f *.o main
