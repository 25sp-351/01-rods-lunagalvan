CFLAGS = -g -Wall

all: main

program: main.o
	clang $(CFLAGS) -o main main.o

main.o: main.c
	clang $(CFLAGS) -c main.c

clean:
	rm -f *.o program
