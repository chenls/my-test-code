#include <stdio.h>

extern int g_share;
extern int g_func2(int a);

int main() {
  int a = 42;
  a = g_func2(a);
  printf("a = %d\n", a);
  return 0;
}
