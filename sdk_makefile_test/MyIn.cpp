#include "MyIn.h"
#include "MyLib.h"
#include <stdio.h>

MyLib myLib;

double test() {
  double a = myLib.test2(6.3);
  printf("%s: %lf\n", __func__, a);
  return a;
}