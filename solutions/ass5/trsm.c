#include <stdlib.h>
#include <stdio.h>
#include <time.h> // for timing the execution
#include "utils.h"

#define TS ((double) clock())/CLOCKS_PER_SEC
#define CYCLES (int) pow(10, 1000)

// Using macros to make debugging easier

// Solve Lx=y using blas functions
double *trsm(double *, double *, int, int);
double *gen_matrix(int);
double pow(double, double);

int debug = 1;

// this should be the definition from common_level2.h
double *trsv(long, double *, long, double *, long, void *);

int main(int argc, char *argv[])
{
  int n, b, i;
  double ctime, tot_time;
  double *L, *y, *x;

  if (argc != 3) {
    printf("usage: ./trsm <n> <b>\n");
    return(-1);
  }
  // Using strtol instead of atoi which is deprecated
  n = (int)strtol(argv[1], (char **)NULL, 10);
  b = (int)strtol(argv[2], (char **)NULL, 10);

  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 

  // Generating needed random data
  y = malloc(sizeof(double) * n);
  L = gen_matrix(n);
  
  // y is a vector of random values
  for (i = 0; i < n; i++)
    y[i] = drand48();

  // compute the result and time the execution
  ctime = TS;
  for (i = 0; i < CYCLES; i++) {
    // not right, every time reassign everything
    x = trsm(L, y, n , b);
    free(x);
  }
  // we only need the total time not the peak
  tot_time = TS - ctime;

  printf("matrix L\n");
  print_double_matrix(L, n);
  
  printf("vector y\n");
  print_double_vector(y, n);

  printf("resulting vector x, %d computations took %.4f seconds \n", CYCLES, tot_time);
  print_double_vector(x, n);

  // finally cleaning the memory
  free(y);
  free(L);
  //  free(x);
  return 0;
}


// add a more general way to print a matrix

double * gen_matrix(int n) {
  int i, j, idx;
  // we before set the seed for the random function to be called later
  double *bigl = malloc(sizeof(double) * n * n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      idx = j*n + i;
      bigl[idx] = drand48(); // setting to a random double <0,1>

      if (i == j)
	bigl[idx] += n;
    }
  }
  return bigl;
}


double *trsm(double *L, double *y, int n, int b) {
  double *x = malloc(sizeof(double) * n);
  return x;
  // we must print when computed
  // n, ||Lx − y||, and the execution time for TRSV
}
