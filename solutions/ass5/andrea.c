#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

double *gen_L(int);

int main(int argc, char *argv[])
{
  // initialization of ithe seed is done once for all
  srand48( (unsigned)time((time_t *) NULL )); 
  double *L;
  
  L = gen_L(5);
    
  return 0;
}

// must be equivalent to rand(n) + n * eye(n)
double *gen_L(int len) {
  int i, j, pos;
  int tri_len = (len * (len + 1)) / 2; // using Gauss formula to allocate as least as possible
  double *L = (double *) malloc(sizeof(double) * tri_len);
  
  pos = 0;
  for (i = 0; i < len; i++) {
    for (j = 0; j <= i; j++) {
      //printf("pos = %d\n", pos);
      L[pos] = drand48();
      if (i == j)
	L[pos] += len;
      printf("%.4f\t", L[pos]);
      pos++;
    }
    printf("\n");
  }
  return L;
}
