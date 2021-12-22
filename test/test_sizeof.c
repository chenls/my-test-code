#include <stdio.h>
#include <string.h>

void f(char *name) { printf("22 %lu %lu\n", strlen(name), sizeof(name)); }

int main(int argc, char const *argv[]) {
  char name[128] = "abc";
  printf("11 %lu %lu\n", strlen(name), sizeof(name));
  f(name);
  return 0;
}
