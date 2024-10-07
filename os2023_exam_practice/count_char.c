#include <err.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define BLK_SZ 4096

int main(int argc, char ** argv) {
  int idx = 1;
  char * file = (idx < argc ? argv[idx++] : "wikipedia-operating-system.html");
  char c =      (idx < argc ? argv[idx++][0] : 'a');
  int fd = open(file, O_RDONLY);
  if (fd == -1) err(1, "open");
  char a[BLK_SZ];
  ssize_t count = 0;
  while (1) {
    int rd = read(fd, a, BLK_SZ);
    if (rd == -1) err(1, "read");
    for (ssize_t i = 0; i < rd; i++) {
      if (a[i] == c) count++;
    }
    if (rd == 0) break;
  }
  printf("%ld\n", count);
  return 0;
}
