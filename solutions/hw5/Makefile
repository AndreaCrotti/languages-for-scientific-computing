# FIXME: this path must be usable also by the professor
BLAS = $(HOME)/libs/c/blas
CC = gcc
DEBUG = -g
CFLAGS = -Wall $(DEBUG)
LINK = -L$(BLAS) -lgoto -lg2c -lpthread
SOURCES = andrea.c trsv.c utils.c
TARFILE = andrea_crotti.tar.gz

all : clean trsv andrea

utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsv : utils
	$(CC) $(CFLAGS) $(LINK) -c trsv.c
	$(CC) -o trsv trsv.o utils.o

andrea :
	$(CC) $(CFLAGS) -o andrea andrea.c

clean:
	rm -f *.o

tar : 
	tar -cvzf $(TARFILE) $(SOURCES)
