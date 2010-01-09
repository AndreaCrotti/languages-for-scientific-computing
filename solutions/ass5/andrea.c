#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "utils.h"

#define LEN 10
// macro useful to pass from array index to position
#define IDX_TO_CONT(i, l, s) ((i+1)*s + l)

#define OUTPUT_FILE "output.m"

// To test my result print them to file and then load the results in octave

double *my_trsv(double *, double *, int);
int check_trsv(double *L, double *y, int len,
	       double * (*trsv)(double *, double *, int));

int main(int argc, char *argv[])
{
  // for lazyness we'll assume that the arguments are passed correctly
  int n, i, len;
  double ctime, tot_time;
  double *L, *x, *y;
  // seeding the random generator
  srand48( (unsigned)time((time_t *) NULL )); 

  if (argc == 2) {
    // In this case execute once and return execution time
    n = (int)strtol(argv[1], (char **)NULL, 10);
    // a generic function timer should take the function pointer as argument
    ctime = TS;
    tot_time = TS - ctime;
    printf("execution time was: %f\n;", tot_time);
  }
  
  else if (argc == 5) {
    int l, r, s, sw;

    l = (int)strtol(argv[1], (char **)NULL, 10);
    r = (int)strtol(argv[2], (char **)NULL, 10);
    s = (int)strtol(argv[3], (char **)NULL, 10);
    sw = (int)strtol(argv[4], (char **)NULL, 10);

    n = (int)((r - l) / s);
    
    double *times = malloc(sizeof(double) * n); // this remains in the stack

    for ( i = 0; i < n; i++ ) {
      len = IDX_TO_CONT(i, l, s);
      L = gen_rand_tril(len);
      y = gen_rand_vector(len);

      ctime = TS;
      x = my_trsv(L, y, len);
      times[i] = TS - ctime;
            
      //printf("time spent for len %d = %.6f\n", len, times[i]);

      free(L); free(y); free(x);
    }
    printf("writing output to file %s\n", OUTPUT_FILE);

    FILE *output = fopen(OUTPUT_FILE, "w");

    if (sw == 0) {
      //producing the plot
    }
    if (sw == 1) {
      // producing the 2 vectors
      char ticks[] = "andreaticks = [ %d:%d:%d ]\n";
      char tim[] = "andreatimes = ";
      // and then add both to it
      fprintf(output, ticks, l, s, r);
      fprintf(output, tim);
      print_vector_to_matlab(output, times, n);
    }

    fclose(output);
    free(times);
  }
  else {
    printf("usage:\n./andrea n\nandrea l r s 0|1\n");
    return(-1);
  }
  return 0;
}


// put in x the result of the computation
double *my_trsv(double *L, double *y, int len) {
  // one advice is to use the upper part of the matrix for temp space
  int i, j, before;
  double *x = (double *) malloc(sizeof(double) * len);
  for (i = 0; i < len; i++) {
    before = 0;
    for (j = 0; j < i; j++) {
      before += L[i*len + j] * x[j];
    }
    x[i] = (y[i] - before) / L[i*(len + 1)]; // equal to L[i][i]
  }
  // Finally use the norm2 to check if the result is close enough to 0
  return x;
}

// checking correctness of our algorithm
int check_trsv(double *L, double *y, int len,
	       double * (*trsv)(double *, double *, int)) {

  double *x = malloc(sizeof(double) * len);
  x = (*trsv) (L, y, len);
  return 0;
}
