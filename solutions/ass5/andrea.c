#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

#define LEN 10

// To test my result print them to file and then load the results in octave

double *my_trsv(double *, double *, int);

int main(int argc, char *argv[])
{
  // getting options from the command line
  // for lazyness assume that the arguments are passed correctly
  int n, i, len;
  double ctime, tot_time;
  double *L, *x, *y;
  // for random generator
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
    
    struct timing times[n];
    // (double *) malloc(sizeof(double) * n);

    // a double initialization and increment
    // not really elegant
    printf("l = %d, r = %d, s = %d\n", l, r, s);
    for  (i = 0, len = l; len <= r; i++, len += s) {
      printf("len = %d", len);
      // everytime generate a new matrix
      L = gen_rand_tril(len);
      y = gen_rand_vector(len);

      ctime = TS;
      x = my_trsv(L, y, len);
      tot_time = TS - ctime;

      times[i].size = len;
      times[i].time = tot_time;
      
      print_timing(times[i]);
      free(L); free(y); free(x);
    }

    if (sw == 0) {
      //producing the plot
    }
    if (sw == 1) {
      // producing the 2 vectors
    }
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
      before += L[i*len + j]*x[j];
    }
    x[i] = (y[i] - before) / L[i*(len + 1)]; // equal to L[i][i]
  }
  // Finally use the norm2 to check if the result is close enough to 0
  return x;
}
