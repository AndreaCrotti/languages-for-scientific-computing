#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for memcpy
#include <time.h> // for timing the execution
#include "utils.h"

#define CYCLES (long) pow(10, 1000)
#define DEBUG 1

// TODO: compile BLAS first

// Solve Lx=y using blas functions
double *wrap_trsv(double *, double *, int, int);
double pow(double, double);

void run(int, int);

// definition from the fortran interface (see _)
int dtrsv_(char *, char *, char *, int *, double *, int *, double *, int *);

int main(int argc, char *argv[])
{
  int n, b;
  if (argc != 3) {
    printf("usage: ./trsv <n> <b>\n");
    return(-1);
  }
  // Using strtol instead of atoi which is deprecated
  n = (int)strtol(argv[1], (char **)NULL, 10);
  b = (int)strtol(argv[2], (char **)NULL, 10);

  run(n, b);
  
  return 0;
}

void run(int n, int b) {
  int i;
  double *L, *y, *x;
  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 

  // Generating needed random data
  y = malloc(sizeof(double) * n);
  L = gen_rand_tril(n);
  
  // y is a vector of random values
  for (i = 0; i < n; i++)
    y[i] = drand48();

  printf("matrix L:\n");
  print_double_matrix(L, n);
  
  printf("vector y:\n");
  print_double_vector(y, n);

  // compute the result and time the execution
#ifdef TIMING
  double ctime, tot_time;
  ctime = TS;
  for (i = 0; i < CYCLES; i++) {
    // not right, every time reassign everything
    wrap_trsv(L, y, n , b);
  }
  tot_time = TS - ctime;
  // FIXME: error in string formatting
  printf("computing %l times took %l seconds \n", CYCLES, (long) tot_time);
#endif

  printf("resulting vector x:\n");
  x = wrap_trsv(L, y, n, b);
  print_double_vector(x, n);

  // finally cleaning the memory
  free(y);
  free(L);
  free(x);
}


double *wrap_trsv(double *L, double *y, int n, int b) {
  double *x = (double *) malloc(sizeof(double) * n);
  
  // prepare the arguments to give to the dtrsv_ function
  /* char *up_lo = "l"; */
  /* char *trans = "T"; */
  /* char *diag = "n"; */
  /* int order = n; */
  /* int incx = 1; */
  // copy y vector to x, y should be untouched, right?
  memcpy(x, y, sizeof(double) * n);

  //dtrsv_(up_lo, trans, diag, &order, L, &n, x, &incx);
  return x;
  // ||Lx - y|| = 0 if it's correct
  // n, ||Lx − y||, and the execution time for TRSV
  // it can't be 0 given that we work with floating point but it should be very close.
}
