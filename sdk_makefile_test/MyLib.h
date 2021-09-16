#include <stdio.h>
class MyLib {
public:
  MyLib() { printf("MyLib\n"); }
  int init();
  double test2(double x);
  int fini();
  ~MyLib() { printf("~MyLib\n"); }
};