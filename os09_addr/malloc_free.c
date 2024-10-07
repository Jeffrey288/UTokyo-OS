#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  long n = (argc > 1 ? atol(argv[1]) : 10);
  long repeat = (argc > 1 ? atol(argv[1]) : 5);
  if (n > 1000) {
    fprintf(stderr, "n (%ld) too large (> 1000)\n", n);
  }
  printf("allocate 100MB blocks %ld x %ld times, retaining %ld blocks\n",
         n, repeat, n);
  void * a[n];
  for (long r = 0; r < n; r++) {
    for (long i = 0; i < n; i++) {
      if (r > 0) free(a[i]);
      a[i] = malloc(100 * 1000 * 1000);
      printf("a@main() :     %ld\n", a[i]);
    }
  }
}
