#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

#define DEBUG 0
#define LEN 10

// To test my result print them to file and then load the results in octave

double *gen_L(int);
double *my_trsv(double *, double *, int);

int main(int argc, char *argv[])
{
  int i;
  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 
  double *L, *y, *x;
  
  printf("L:\n");
  L = gen_L(LEN);
  print_double_matrix(L, LEN);
  
  // Generating needed random data
  y = malloc(sizeof(double) * LEN);
  
  // y is a vector of random values
  for (i = 0; i < LEN; i++)
    y[i] = drand48();
  
  printf("y:\n");
  print_double_vector(y, LEN);
  x = my_trsv(L, y, LEN);
  
  printf("x:\n");
  print_double_vector(x, LEN);
  // finally free the memory
  free(L);
  free(y);
  free(x);
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
  }
  return L;
}

double *my_trsv(double *L, double *y, int len) {
  int i, j, before;
  double *x = (double *) malloc(sizeof(double) * len);
  for (i = 0; i < len; i++) {
    before = 0;
    for (j = 0; j < i; j++) {
      before += L[i*len + j]*x[j];
    }
    x[i] = (y[i] - before) / L[i*(len + 1)]; // equal to L[i][i]
  }
  return x;
}

/**********************************************************/
/* def solve(L, y):					  */
/*     "Return x such that L*x = y where L is triangular" */
/*     x = [None]*len(L)				  */
/*     for i in range(len(x)):				  */
/*         before = sum(L[i][j]*x[j] for j in range(i))	  */
/*         x[i] = float(y[i] - before) / L[i][i]	  */
/*     return x						  */
/**********************************************************/
