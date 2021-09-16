#include <stdio.h>
class MyLib {
public:
  MyLib() { printf("MyLib\n"); }
  double test2(double x);
  ~MyLib() { printf("~MyLib\n"); }
};