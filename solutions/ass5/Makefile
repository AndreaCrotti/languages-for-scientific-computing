# FIXME: this path must be usable also by the professor
BLAS = $(HOME)/libs/c/blas
CC = gcc
OPTIMIZE = -O3 # apple only
CFLAGS = -Wall -g $(OPTIMIZE)
LINK = -L$(BLAS) -lgoto -lg2c -lpthread
SOURCES = andrea.c trsm.c utils.c
TARFILE = andrea_crotti.tar.gz

all : clean trsm andrea

utils : utils.o
	$(CC) $(CFLAGS) -c utils.c

trsm : utils
	$(CC) $(CFLAGS) $(LINK) -c trsm.c
	$(CC) -o trsm trsm.o utils.o

andrea :
	$(CC) $(CFLAGS) -o andrea andrea.c

clean:
	rm -f *.o

tar : 
	tar -cvzf $(TARFILE) $(SOURCES)
