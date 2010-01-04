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
      printf("%.3f\t", matrix[i*dim + j]);
    printf("\n");
  }
}

void print_double_vector(double *vector, int len) {
  int i;
  
  for (i = 0; i < len; i++)
    printf("%.3f\t", vector[i]);
  printf("\n");
}

double *gen_rand_matrix(int n) {
  int i, j, idx;
  // we before set the seed for the random function to be called later
  double *bigl = malloc(sizeof(double) * n * n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      idx = i*n + j;
      bigl[idx] = drand48(); // setting to a random double <0,1>

      if (i == j)
	bigl[idx] += n;
    }
  }
  return bigl;
}

// tries to write to a .m file the square matrix given
int write_to_m(double *matrix, int len, char *filename) {
  FILE *output = fopen(filename, "w");
  // Using fprintf or fwrite?
  // not able to open it
  if (output == NULL) {
      printf("not able to open the file");
      return 0;
  }
  int i, j;
  
  fprintf(output, "[");
  for (i = 0; i < len; i++) {
    fprintf(output, "[");
    for (j = 0; j < len; j++) {
      fprintf(output, "%.4f ", matrix[i*len + j]);
    }
    fprintf(output, "]\n");
  }
  fprintf(output, "]");
  fclose(output);
  return 1;
}

// creates a random matrix and writes it to filename
int test_write_to_m(int len, char *filename) {
  int ret;
  double *test_m = gen_rand_matrix(len);
  ret = write_to_m(test_m, len, filename);
  return ret;
}
