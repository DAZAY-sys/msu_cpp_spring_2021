CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address

all: main

main: test.o matrix.o
	$(CC) $(FLAGS) test.o matrix.o -o main

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) matrix.cpp -c

test.o: test.cpp matrix.hpp
	$(CC) $(FLAGS) test.cpp -c

test: main
	./main

clean:
	rm -f *.o main