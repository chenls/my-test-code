#include "mylib1.h"
#include "mylib2.h"
#include "mylib3.h"
#include <stdio.h>

double mylib2(double __x) { return __x * 3; }

int main() {
  double a = mylib1(6.3);
  printf("%lf\n", a);

  double b = mylib2(6.3);
  printf("%lf\n", b);

  double c = mylib3(6.3);
  printf("%lf\n", c);

  // double p = mylib_public(6.3);
  // printf("%lf\n", p);
}