#include <stdio.h>
#include "utils.h"

int main(int argc, char *argv[])
{
  printf("testing write_to_m");
  int r = test_write_to_m(10, "output.m");
  printf("we got %d\n", r);
  
  printf("testing something else");
  return 0;
}
