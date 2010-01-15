// This simple shell script can see the accuracy

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for memcpy
#include <time.h> // for timing the execution
#include <math.h> // power
#include "utils.h"

#define POW 5

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
  double ctime, tot_time, err;
  long i;
  // FIXME:overflowing here? why?
  long cycles = powl(10, POW);

  // arguments for dtrsv function
  char *up_lo = "l";
  char *trans = "T";
  char *diag = "n";
  int incx = 1;

  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 

  // Generating needed random data
  L = gen_rand_tril(n);
  y = gen_rand_vector(n);

  ctime = TS;
  double *oldy = (double *) malloc(sizeof(double)*n);
  
  for (i = 0; i < cycles; i++) {
    // I have to save the old y every time
    memcpy(oldy, y, sizeof(double)*n);
    dtrsv_(up_lo, trans, diag,
  	   &n, L, &n, oldy, &incx);
  }
  tot_time = TS - ctime;
  
  err = error(L, y, oldy, n);
  
  printf("n=%d\n", n);
  printf("error=%"PRECISION"\n", err);
  printf("executing %ld times took %f seconds\n", cycles, tot_time);

  // finally cleaning the memory
  free(y); free(L); free(oldy);
}
