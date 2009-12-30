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

utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsv : 
	$(CC) $(CFLAGS) -o trsv trsv.c

andrea :
	$(CC) $(CFLAGS) -o andrea andrea.c

clean:
	rm trsv andrea

tar : 
	tar -cvzf andrea_crotti.tar.gz andrea.c trsv.c
