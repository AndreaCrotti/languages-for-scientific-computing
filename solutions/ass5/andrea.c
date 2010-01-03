#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

#define DEBUG 0

double *gen_L(int);
double *my_trsv(double *, double *);

int main(int argc, char *argv[])
{
  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 
  double *L;
  
  L = gen_L(5);
  print_double_matrix(L, 5);
  
  // finally free the memory
  free(L);
  return 0;
}

// must be equivalent to tri(rand(n) + n * eye(n))
double *gen_L(int len) {
  int i, j, pos;
  // using calloc  set it to 0 automatically
  double *L = (double *) calloc(len*len, sizeof(double));
  
  for (i = 0; i < len; i++) {
    for (j = 0; j <= i; j++) {
      pos = i*len + j;
      if (DEBUG)
	printf("i, j, pos = %d, %d, %d\n", i, j, pos);
      L[pos] = drand48();
      if (i == j)
	L[pos] += len;

    }
    printf("\n");
  }
  return L;
}

double *my_trsv(double *L, double *y, int len) {
  double *x = (double *) malloc(sizeof(double) * len);
  
  return x;
}
