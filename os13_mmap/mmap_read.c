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
  char * filename = (argc > i ? argv[i] : "mmap_1.c"); i++;
  /* ファイルを開く */
  int fd = open(filename, O_RDONLY);
  if (fd == -1) err(1, "open");
  /* ファイルのサイズ */
  struct stat sb[1];
  if (fstat(fd, sb) == -1) err(1, "fstat");
  /* mmap (読み出しのみ) */
  long sz = sb->st_size;
  char * a = mmap(0, sz, PROT_READ, MAP_PRIVATE, fd, 0);
  if (a == MAP_FAILED) err(1, "mmap");
  /* 配列aを表示すると filename の中身を表示することになる*/
  for (long i = 0; i < sz; i++) {
    putchar(a[i]);
  }
  if (munmap(a, sz) == -1) err(1, "mumap");
  if (close(fd) == -1) err(1, "close");
  return 0;
}
