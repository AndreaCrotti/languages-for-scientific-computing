#include <stdlib.h>
#include <stdio.h>
#include <time.h> // for timing the execution

// Using macros to make debugging easier

// Solve Lx=y using blas functions
void trsv(double **, double *, int, int);
double *gen_matrix(int);
int debug = 1;

int main(int argc, char *argv[])
{
  // Use getopts to get the options
  
  int n, b, i;
  n = (int)strtol(argv[1], (char **)NULL, 10);
  b = (int)strtol(argv[2], (char **)NULL, 10);

  // once for all initialization is enough
  srand48( (unsigned)time((time_t *) NULL )); 
  printf ("got n = %d and b = %d\n", n, b);

  double *y = malloc(sizeof(double) * n);
  gen_matrix(n);

  // y is a vector of random values
  for (i = 0; i < n; i++)
    y[i] = drand48();
  
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

      if (debug)
	printf("%f\t", bigl[idx]);

      // FIXME: this is never executed
      if (i == j)
	bigl[idx] += n * 1.0;
    }
    printf("\n");
  }
  return bigl;
}

void trsv(double **L, double *y, int n, int b) {
  
  // we must print when computed
  // n, ||Lx − y||, and the execution time for TRSV
}
