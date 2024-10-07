#include <stdio.h>

void g() {
  int x = 20;
  printf("x@g : %ld = %d\n", &x, x);
}

void f() {
  int x = 10;
  g();
  printf("x@f : %ld = %d\n", &x, x);
}

int main() {
  f();
  return 0;
}
