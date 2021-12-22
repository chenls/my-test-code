#include "stdlib.h"
#include <stdio.h>

/*打桩函数*/
void *mymalloc(size_t size) {
  void *ptr = malloc(size);
//   printf("ptr is %p\n", ptr);
  return ptr;
}