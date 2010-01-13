# Customize those 2 variables is enough
BLAS = $(HOME)/libs/c/GotoBLAS
CC = gcc

OPTIMIZE = -O0 # disable optimization
DEBUG = -g
CFLAGS = -Wall $(DEBUG) $(OPTIMIZE)

SOURCES = andrea.c trsv.c trsv.m output.m graph.m utils.c utils.h Makefile
TARFILE = andrea_crotti.tar.gz

all : clean trsv andrea

# how is make calling an implicit rule and compiling utils twice?
utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsv : utils
	$(CC) $(CFLAGS) -c trsv.c
	$(CC) -L$(BLAS) -o trsv -lm -lblas trsv.o utils.o

andrea : utils
	$(CC) $(CFLAGS) -c andrea.c
	$(CC) -lm -o andrea andrea.o utils.o

clean :
	rm -f *.o

# with the all requirment it's only tarred up when everything compiles
tar : 	all
	tar -cvzf $(TARFILE) $(SOURCES)
