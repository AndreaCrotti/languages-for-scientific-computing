#include <stdio.h>
#include "utils.h"

int main(int argc, char *argv[])
{
  double L[] = {1, 0, 1, 1};
  double y[] = {1, 1};
  double x[] = {1, 0};
  
  printf("accuracy for sample is %f\n", accuracy(L, y, x, 2));
  return 0;
}
