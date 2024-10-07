#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <err.h>

int compare_int(const void * a_, const void * b_) {
  const int * a = a_;
  const int * b = b_;
  return *a - *b;
}

int main(int argc, char ** argv) {
  // https://stackoverflow.com/questions/43674522/how-is-char-to-string-literal-valid
  char * filename = (argc > 1 ? argv[1] : "sorted.bin");
  int key = (argc > 2 ? atoi(argv[2]) : 100);
  // int key = 362382304;
  int fd = open(filename, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  int fd_size = st.st_size;
  // printf("%d\n", fd_size);
  int num_numbers = fd_size / sizeof(int); // divide by 4
  if (num_numbers != 256 * 1024 * 1024) err(-1, "num_numbers");

  int* a = mmap(0, fd_size, PROT_READ, MAP_SHARED, fd, 0);
  if (a == MAP_FAILED) err(1, "mmap");

  int* found = bsearch(&key, a, num_numbers, sizeof(int), compare_int);
  if (found) {
    printf("%d found at %ld-th element\n", key, found - a);
  } else {
    printf("%d not found\n", key);
  }
  return 0;
}
