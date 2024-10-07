#include <assert.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv) {
  int i = 1;
  long sz         = (argc > i ? atol(argv[i]) : 1000); i++;
  /* mmap メモリ割当のみ */
  char * a = mmap(0, sz, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if (a == MAP_FAILED) err(1, "mmap");
  /* これは単なるメモリ割り当て */
  for (long i = 0; i < sz; i++) {
    assert(a[i] == 0);
  }
  if (munmap(a, sz) == -1) err(1, "mumap");
  printf("OK\n");
  return 0;
}
