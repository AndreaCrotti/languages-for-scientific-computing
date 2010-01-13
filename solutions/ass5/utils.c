// implementation of some useful functions on matrices
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils.h"

void print_double_matrix(double *matrix, int dim) {
  int i, j;

  for (i = 0; i < dim; i++) {
    printf("\t");
    for (j = 0; j < dim; j++)
      printf("%"PRECISION"\t", matrix[i*dim + j]);
    printf("\n");
  }
}

void print_double_vector(double *vector, int len) {
  int i;
  printf("\t");
  for (i = 0; i < len; i++)
    printf("%"PRECISION"\t", vector[i]);
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

void print_vector_to_matlab(FILE *output, double *vector, int len) {
  int i;
  fprintf(output, "[ ");
  for (i = 0; i < len; i++) {
    fprintf(output, "%"PRECISION" ", vector[i]);
  }
  fprintf(output, "]\n");
}

double norm(double *vector, int len) {
  int i;
  double norm = 0;
  // sum the squares and then output the square root
  for (i = 0; i < len; i++) {
    norm += pow(vector[i], 2);
  }
  return sqrt(norm);
}

// returns the accuracy of my solution return ||Lx - y||
double error(double *L, double *y, double *x, int len) {
  double *lx = (double *) malloc(sizeof(double) * len);
  int i, j;
  double error;
  
  for (i = 0; i < len; i++) {
    // substracting y in initialization time
    lx[i] = -y[i];
    for (j = 0; j < len; j++) {
      lx[i] += L[i*len + j] * x[j];
    }
  }
  error = norm(lx, len);
  // this style of malloc/free is not very convincing
  free(lx);
  return error;
}
