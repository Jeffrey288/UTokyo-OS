#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <err.h>
#include <unistd.h>

int main(int argc, char ** argv) {
  char * filename = (argc > 1 ? argv[1] : "sorted.bin");
  int key = (argc > 2 ? atoi(argv[2]) : 100);

  int fd = open(filename, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  int fd_size = st.st_size;
  int num_numbers = fd_size / sizeof(int); // divide by 4
  if (num_numbers != 256 * 1024 * 1024) err(-1, "num_numbers");

  // Allocate memory dynamically using mmap
  const int how_many_numbers_read_at_a_time = 1024;
  int a[how_many_numbers_read_at_a_time];
  int numbers_read = 0;

  int found = -1;
  while (numbers_read < num_numbers) {
      if (read(fd, a, how_many_numbers_read_at_a_time * sizeof(int)) != how_many_numbers_read_at_a_time * sizeof(int)) err(-1, "read");
      for (int i = 0; i < how_many_numbers_read_at_a_time; i++) {
          if (a[i] == key) {
              found = numbers_read + i;
              break;
          }
      }
      if (a[how_many_numbers_read_at_a_time - 1] > key) break;
      if (found != -1) break;
      numbers_read += how_many_numbers_read_at_a_time;
  }

  if (found != -1) {
    printf("%d found at %d-th element\n", key, found);
  } else {
    printf("%d not found\n", key);
  }
  return 0;

}
