#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "utils.h"

// Can I also set a global parameter LEN (not a macro)

// macro useful to pass from array index to position
#define IDX_TO_CONT(i, l, s) ((i+1)*s + l)

#define OUTPUT_FILE "output.m"
#define OUTPUT_GRAPH "graph.m"

// To test my result print them to file and then load the results in octave

void forward_trsv(double *, double *, int);
void forward_trsv_over(double *, double *, int);
int check_trsv(double *L, double *y, int len,
	       void (*trsv)(double *, double *, int));

int main(int argc, char *argv[])
{
  // for lazyness we'll assume that the arguments are passed correctly
  int n, i, len;
  double ctime, tot_time;
  double *L,*y;
  // seeding the random generator
  srand48( (unsigned)time((time_t *) NULL )); 

  if (argc == 2) {
    // In this case execute once and return execution time
    n = (int)strtol(argv[1], (char **)NULL, 10);

    L = gen_rand_tril(n);
    y = gen_rand_vector(n);

    // a generic function timer should take the function pointer as argument
    ctime = TS;
    
    // calling the function itself
    check_trsv(L, y, n, (* forward_trsv));

    tot_time = TS - ctime;
    printf("execution time was: %f\n;", tot_time);
    free(L); free(y);
  }
  
  else if (argc == 5) {
    int l, r, s, sw;

    l = (int)strtol(argv[1], (char **)NULL, 10);
    r = (int)strtol(argv[2], (char **)NULL, 10);
    s = (int)strtol(argv[3], (char **)NULL, 10);
    sw = (int)strtol(argv[4], (char **)NULL, 10);

    n = ((r - l) / s) + 1;
    
    double *times = malloc(sizeof(double) * n); // this remains in the stack

    for ( i = 0; i < n; i++ ) {
      len = IDX_TO_CONT(i, l, s);

      L = gen_rand_tril(len);
      y = gen_rand_vector(len);

      ctime = TS;
      forward_trsv(L, y, len);
      times[i] = TS - ctime;

      free(L); free(y);
      //printf("time spent for len %d = %.6f\n", len, times[i]);
    }
    printf("writing output to file %s\n", OUTPUT_FILE);

    // we assume that the input from the comma
    FILE *output = fopen(OUTPUT_FILE, "w");

    // producing the 2 vectors
    char ticks[] = "andreaticks = [ %d:%d:%d ]\n";
    // and then add both to it
    fprintf(output, ticks, l, s, r);
    fprintf(output, "andreatimes = ");
    print_vector_to_matlab(output, times, n);
    fclose(output);

    if (!sw)
      printf("graph.m is already generated and made general\n");

    free(times);
  }
  else {
    printf("usage:\n\tandrea n\n\tandrea l r s 0|1\n");
    return(-1);
  }
  return 0;
}

// try to optimize this in some ways
void forward_trsv(double *L, double *y, int len) {
  // one advice is to use the upper part of the matrix for temp space
  int i, j;
  double *x = (double *) malloc(sizeof(double) * len);
  for (i = 0; i < len; i++) {
    x[i] = y[i];
    for (j = 0; j < i; j++) {
      x[i] -= L[i*len + j] * x[j];
    }
    x[i] /= L[i*(len + 1)];
  }
  memcpy(y, x, sizeof(double)*len);
  free(x);
}

// checking correctness of our algorithm
int check_trsv(double *L, double *y, int len,
	       void (*trsv)(double *, double *, int)) {

  double err;
  double *y_temp = malloc(sizeof(double) * len);
  memcpy(y_temp, y, sizeof(double)*len);

  (*trsv) (L, y, len);
  
  err = error(L, y_temp, y, len);
  printf("error obtained is %.10f\n", err);
  free(y_temp);
  return 0;
}
