#include "mylib1.h"
#include "mylib2.h"
#include <stdio.h>

int main() {
  double a = mylib1(6.3);
  printf("%lf\n", a);

  double b = mylib2(6.3);
  printf("%lf\n", b);
}