#include <stdio.h>
#include <stdlib.h>

int main() {
  char *p = malloc(64);
  free(p);
  return 0;
}