#include <stdio.h>

long fib(long n) {
  printf("n@fib(%ld) : %ld\n", n, (long)&n);
  if (n < 2) {
    return 1;
  } else {
    long x = fib(n - 1);
    long y = fib(n - 2);
    printf("x@fib(%ld) : %ld\n", n, (long)&x);
    printf("y@fib(%ld) : %ld\n", n, (long)&y);
    return x + y;
  }
}

int main() {
  long n = 10;
  long x = fib(n);
  printf("fib(%ld) = %ld\n", n, x);
  return 0;
}
