# FIXME: this path should be autoconfigurable
BLAS = $(HOME)/libs/c/GotoBLAS
CC = gcc
OPTIMIZE = -O0 # disable optimization
# Adding some timing / profiling targets??
PROFILE = -pg
CFLAGS = -Wall -g $(OPTIMIZE)
LINK = -L$(BLAS) -lgoto -lg2c -lm
SOURCES = andrea.c trsv.c trsv.m test.c output.m utils.c utils.h Makefile
TARFILE = andrea_crotti.tar.gz

all : clean trsv andrea test

utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsv : utils
	$(CC) $(CFLAGS) $(LINK) -c trsv.c
	$(CC) -o trsv trsv.o utils.o

andrea : utils
	$(CC) $(CFLAGS) -c andrea.c
	$(CC) -o andrea andrea.o utils.o

test : utils
	$(CC) $(CFLAGS) -c test.c
	$(CC) -o test test.o utils.o

clean:
	rm -f *.o

# do some checking
tar : 
	tar -cvzf $(TARFILE) $(SOURCES)
