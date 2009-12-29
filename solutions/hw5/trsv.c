#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Solve Lx=y using blas functions
void trsv(double **, double *, int, int);

int main(int argc, char *argv[])
{
  // Use getopts to get the options
  
  int n, b;
  double *y;
  // getting the arguments from the command line
  // working now
  n = (int)strtol(argv[1], (char **)NULL, 10);
  b = (int)strtol(argv[2], (char **)NULL, 10);

  printf ("got n = %d and b = %d\n", n, b);
  // y is a vector of random values
  y = malloc(sizeof(double) * n);
  return 0;
}


void trsv(double **L, double *y, int n, int b) {
  
  // we must print when computed
  // n, ||Lx − y||, and the execution time for TRSV
}
