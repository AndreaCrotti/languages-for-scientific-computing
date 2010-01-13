# FIXME: this path should be autoconfigurable
BLAS = $(HOME)/libs/c/GotoBLAS
CC = gcc
OPTIMIZE = -O0 # disable optimization
# Adding some timing / profiling targets??
CFLAGS = -Wall -g $(OPTIMIZE)
LINK = -lblas -lm
SOURCES = andrea.c trsv.c trsv.m test.c output.m graph.m utils.c utils.h Makefile
TARFILE = andrea_crotti.tar.gz

all : clean trsv andrea test

utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsv : utils
	$(CC) $(CFLAGS) $(LINK) -c trsv.c
	$(CC) -o trsv -lm trsv.o utils.o

andrea : utils
	$(CC) $(CFLAGS) -c andrea.c
	$(CC) -lm -o andrea andrea.o utils.o

test : utils
	$(CC) $(CFLAGS) -c test.c
	$(CC) -lm -o test test.o utils.o

clean :
	rm -f *.o

# In this way it only tar up if everything compiles fine
tar : 	all
	tar -cvzf $(TARFILE) $(SOURCES)
