BLAS = $(HOME)/libs/c/blas
CC = gcc
DEBUG = -g
CFLAGS = -Wall $(DEBUG)
LINK = -L$(BLAS) -lgoto -lg2c -lpthread

all : trsv andrea

run_trsv : trsv
	./trsv

run_andrea : andrea
	./andrea

trsv : 
	$(CC) $(CFLAGS) -o trsv trsv.c

andrea :
	$(CC) $(CFLAGS) -o andrea andrea.c

clean:
	rm -v trsv trsv.o andrea andrea.o
