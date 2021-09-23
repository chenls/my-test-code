#include <stdio.h>

unsigned __attribute__((noinline))
product(unsigned char *a, unsigned char *b, int size) {
  unsigned int sum = 0;

  for (int i = 0; i < size; i++) {
    sum += a[i] * b[i];
  }

  __asm__("UDOT v0.4s, v1.16b, v2.16b");

  return sum;
}

int main() {
  unsigned char a[] = {1, 2, 3};
  unsigned char b[] = {1, 2, 3};
  unsigned int sum = product(a, b, 3);
  printf("sum = %d\n", sum);
  return 0;
}
