CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address

all: main

main: test.o bigint.o
	$(CC) $(FLAGS) test.o bigint.o -o main

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) bigint.cpp -c

test.o: test.cpp bigint.hpp
	$(CC) $(FLAGS) test.cpp -c

test: main
	./main

clean:
	rm -f *.o main
