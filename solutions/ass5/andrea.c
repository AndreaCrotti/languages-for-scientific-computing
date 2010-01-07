#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

#define LEN 10

// To test my result print them to file and then load the results in octave

double *my_trsv(double *, double *, int);

int main(int argc, char *argv[])
{
  // for lazyness assume that the arguments are passed correctly
  int n;
  double *L;
  if (argc == 2) {
    // In this case execute once and return execution time
    n = (int)strtol(argv[1], (char **)NULL, 10);
    L = gen_rand_tril(n);
    // a generic function timer should take the function pointer as argument
    
  }
  
  else if (argc == 5) {
    int l, r, s, sw;
    l = (int)strtol(argv[1], (char **)NULL, 10);
    r = (int)strtol(argv[2], (char **)NULL, 10);
    s = (int)strtol(argv[3], (char **)NULL, 10);
    sw = (int)strtol(argv[4], (char **)NULL, 10);
    
    if (sw == 0) {
      //producing the plot
    }
    if (sw == 1) {
      // producing the 2 vectors
    }
  }

  // getting options from the command line

  int i;
  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 
  double *L, *y, *x;
  
  printf("L:\n");
  L = gen_rand_tril(LEN);
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
