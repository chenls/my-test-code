#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char name[128] = "123";
  char name2[128] = "2222";
  char *container_args[] = {"name", name2};
  // sprintf(name, "%s", argv[1]);
  printf("%p %p\n", container_args[1], name2);
  // memcpy(name2, name, strlen(name));
  memcpy(container_args[0], name, strlen(name));
  // memcpy(name2, argv[1], strlen(argv[1]));

  // printf("%p %p %p\n", container_args[0], container_args[1], name);
  // printf("%p %p %p\n", &container_args[0], &container_args[1], &name);
  // printf("%d %d %d\n", container_args[0], container_args[1], container_args);
  printf("%s %s \n", name, name2);
  printf("%s %s \n", container_args[0], container_args[1]);
  return 0;
}
