#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
int main(int argc, char ** argv) {
  long n = (argc > 1 ? atol(argv[1]) : 3);
  if (n > 1000) {
    fprintf(stderr, "n (%ld) too large (> 1000)\n", n);
  }
  printf("allocating 100MB %ld times\n");
  for (long i = 0; i < n; i++) {
    void * a = sbrk(100 * 1000 * 1000);
    printf("a@main() :     %ld\n", a);
  }
}
