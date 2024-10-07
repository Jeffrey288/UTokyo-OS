#include <stdio.h>

#include <stdlib.h>
int g;
long fact(long n) {
  printf("g : %ld\n", (long)&g);
  printf("n@fact(%ld) : %ld\n", n, (long)&n);
  if (n == 0) {
    return 1;
  } else {
    long r = fact(n - 1);
    printf("r@fact(%ld) : %ld\n", n, (long)&r);
    return n * r;
  }
}

int main(int argc, char ** argv) {
  long n = (argc > 1 ? atol(argv[1]) : 10);
  long x = fact(n);
  printf("fact(%ld) = %ld\n", n, x);
  return 0;
}
