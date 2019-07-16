CC=gcc
CFLAGS=-g -ansi -pedantic-errors -Wall

default: all

all: asort

asort: asort.o
	$(CC) -o asort asort.o

asort.o: asort.c
	$(CC) $(CFLAGS) -c asort.c
 
.PHONY: clean

clean:
	rm -rf asort asort.o
