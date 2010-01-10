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
      printf("%"PRECISION"\t", matrix[i*dim + j]);
    printf("\n");
  }
}

void print_double_vector(double *vector, int len) {
  int i;
  
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
      fprintf(output, "%"PRECISION" ", matrix[i*len + j]);
    }
    fprintf(output, "]\n");
  }
  fprintf(output, "]");
  fclose(output);
  return 1;
}


void print_vector_to_matlab(FILE *output, double *vector, int len) {
  int i;
  fprintf(output, "[ ");
  for (i = 0; i < len; i++) {
    fprintf(output, "%"PRECISION" ", vector[i]);
  }
  fprintf(output, "]\n");
}

/* // generates an auto plotting octave file */
/* void print_plot_generator(FILE *graph, char *stats_file, graph_options *options) { */
/*   char *env = "#!/usr/bin/env octave"; */
  

/*   // starting to print out stuff */
/*   fprintf(graph, env); */
  
/* } */
