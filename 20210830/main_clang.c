#include <stdio.h>

int fun_0() {
  printf("this is a test function. %s: %d\n", __FUNCTION__, __LINE__);
  return 0;
}

int main() {
  fun_0();
  return 0;
}
