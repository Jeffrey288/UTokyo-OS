#include <stdio.h>
#include <stdio.h>
/* 大域配列 */
int c[100];
/* 大域変数i */
int i;

int main() {
  for (i = 0; i <= 100; i++) {
    c[i] = 0;
    printf("done %d\n", i);
  }
  printf("done\n");
}
