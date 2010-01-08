// implementation of some useful functions on matrices
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils.h"

void print_double_matrix(double *matrix, int dim) {
  int i, j;

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++)
      // FIXME set a certain amount of numbers
      printf("%.4f\t", matrix[i*dim + j]);
    printf("\n");
  }
}

void print_double_vector(double *vector, int len) {
  int i;
  
  for (i = 0; i < len; i++)
    printf("%.4f\t", vector[i]);
  printf("\n");
}

double *gen_rand_vector (int len) {
  int i;
  double *y = malloc(sizeof(double) * len);
  
  // y is a vector of random values
  for (i = 0; i < len; i++)
    y[i] = drand48();

  return y;
}

// generates a matrix equivalent to tril(rand(n) + n * eye(n))
double *gen_rand_tril(int len) {
  int i, j, pos;
  // using calloc  set it to 0 automatically, is not really necessary
  double *L = (double *) calloc(len*len, sizeof(double));
  
  for (i = 0; i < len; i++) {
    for (j = 0; j <= i; j++) {
      pos = i*len + j;
      L[pos] = drand48();
      if (i == j)
	L[pos] += len;
    }
  }
  return L;
}

// tries to write to a .m file the square matrix given
int matrix_to_matlab(double *matrix, int len, char *filename) {
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

char *vector_to_matlab(double *vector, int len) {
  // 6 is given by 0.<4 digits of precision>, try to abstract this
  int i;
  int totlen = 4 + len*6 + (len - 1);
  char *result = (char *) malloc(sizeof(char) * totlen);
  // necessary to make it end with \0?
  strcat(result, "[\0");
  for (i = 0; i < len; i++) {
    char temp[6];
    sprintf(temp, "%.4f", vector[i]);
    strcat(result, temp);
    //interleaving a space
    if (i < (len -1))
      strcat(result, " \0");
  }
  strcat(result, " ]\0");
  return result;
}

// creates a random matrix and writes it to filename
int test_write_to_m(int len, char *filename) {
  int ret;
  double *test_m = gen_rand_tril(len);
  ret = matrix_to_matlab(test_m, len, filename);
  return ret;
}
