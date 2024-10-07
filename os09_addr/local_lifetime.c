#include <stdio.h>

double * f(double * a) {
  return a;
}
const int n = 30;
double * alloc() {
  double a[n];
  return f(a);
}

int main() {
  double * a = alloc();
  for (long i = 0; i < n; i++) {
    a[i] = i;
  }
  for (long i = 0; i < n; i++) {
    printf("a[%ld] = %f\n", i, a[i]);
  }
  return 0;
}
