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
  char * filename = (argc > i ? argv[i] : "hogehoge.txt"); i++;
  long sz         = (argc > i ? atol(argv[i]) : 1000); i++;
  /* ファイルを開く */
  int fd = open(filename, O_RDWR|O_TRUNC|O_CREAT, 0777);
  if (fd == -1) err(1, "open");
  if (posix_fallocate(fd, 0, sz) == -1) err(1, "posix_fallocate");
  /* mmap */
  char * a = mmap(0, sz, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (a == MAP_FAILED) err(1, "mmap");
  /* 配列aに書き込むとfilenameに書き込むことになる */
  for (long i = 0; i < sz; i++) {
    a[i] = i % 128;
  }
  if (munmap(a, sz) == -1) err(1, "mumap");
  if (close(fd) == -1) err(1, "close");
  return 0;
}
