// implementation of some useful functions on matrices
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

void print_double_matrix(double *matrix) {
  int sq, i, j;
  sq = (int) sqrt(sizeof(matrix));
  
  for (i = 0; i < sq; i++) {
    for (j = 0; j < sq; j++)
      // FIXME set a certain amount of numbers
      printf("%f\t", matrix[j + i*sq]);
    printf("\n");
  }
}

void print_double_vector(double *vector) {
  int i, len;
  len = sizeof(vector);
  
  for (i = 0; i < len; i++)
    printf("%f\t", vector[i]);
}
