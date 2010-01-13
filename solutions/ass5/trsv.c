// This simple shell script can see the accuracy
// for i in $(jot - 2 1000); do ./andrea $i | grep accuracy; done

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for memcpy
#include <time.h> // for timing the execution
#include <math.h> // power
#include "utils.h"

#define POW 100

void run(int);

// definition from the fortran interface (see _)
int dtrsv_(char *, char *, char *, int *, double *, int *, double *, int *);

int main(int argc, char *argv[])
{
  int n;
  if (argc != 2) {
    printf("usage: ./trsv <n>\n");
    return(-1);
  }
  // Using strtol instead of atoi which is deprecated
  n = (int)strtol(argv[1], (char **)NULL, 10);

  run(n);
  return 0;
}

void run(int n) {
  double *L, *y;
  double ctime, tot_time;
  long i;
  long cycles = powl(10, POW);

  // arguments for dtrsv function
  char *up_lo = "l";
  char *trans = "T";
  char *diag = "n";
  int order = n;
  int incx = 1;

  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 

  // Generating needed random data
  L = gen_rand_tril(n);
  y = gen_rand_vector(n);

  printf("matrix L:\n");
  print_double_matrix(L, n);
  
  printf("vector y:\n");
  print_double_vector(y, n);

  ctime = TS;
  for (i = 0; i < cycles; i++) {
    
  }
  tot_time = TS - ctime;

  printf("computing %ld times the trsv took %f seconds \n", cycles, tot_time);
  printf("resulting vector x:\n");
  print_double_vector(y, n);

  // finally cleaning the memory
  free(y); free(L);
}
