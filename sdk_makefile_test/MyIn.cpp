#include "MyIn.h"
#include "MyLib.h"
#include <stdio.h>

MyLib myLib;

double test() {
  myLib.init();

  double a = myLib.test2(6.3);
  printf("%s: %lf\n", __func__, a);

  myLib.fini();
  return a;
}