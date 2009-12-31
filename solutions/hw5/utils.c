// implementation of some useful functions on matrices
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

void print_double_matrix(double *matrix, int dim) {
  int i, j;

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++)
      // FIXME set a certain amount of numbers
      printf("%.3f\t", matrix[j + i*dim]);
    printf("\n");
  }
}

void print_double_vector(double *vector, int len) {
  int i;
  
  for (i = 0; i < len; i++)
    printf("%.3f\t", vector[i]);
  printf("\n");
}
