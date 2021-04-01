CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable

all: main

main: main.o libparse.a
	$(CC) $(FLAGS) main.o -o main -L. -lparse

parser.o: parser.cpp parser.hpp
	$(CC) $(FLAGS) parser.cpp -c

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

libparse.a: parser.o
	ar rc libparse.a parser.o

test: main
	./main

clean:
	rm -f *.o *.a main
