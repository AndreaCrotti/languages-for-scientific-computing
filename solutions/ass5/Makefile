# FIXME: this path should be autoconfigurable
BLAS = $(HOME)/libs/c/blas
CC = gcc
OPTIMIZE = -O0
CFLAGS = -Wall -g #$(OPTIMIZE)
LINK = -L$(BLAS) -lgoto -lg2c -lpthread
SOURCES = andrea.c trsm.c test.c output.m utils.c utils.h Makefile
TARFILE = andrea_crotti.tar.gz

.PHONY : all

all : clean trsm andrea test

utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsm : utils
	$(CC) $(CFLAGS) $(LINK) -c trsm.c
	$(CC) -o trsm trsm.o utils.o

andrea : utils
	$(CC) $(CFLAGS) -c andrea.c
	$(CC) -o andrea andrea.o utils.o

test : utils
	$(CC) $(CFLAGS) -c test.c
	$(CC) -o test test.o utils.o

clean:
	rm -f *.o

tar : 
	tar -cvzf $(TARFILE) $(SOURCES)
