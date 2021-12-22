#include_next <stdlib.h>

#define malloc(size) mymalloc(size)

void *mymalloc(size_t size) {
  void *ptr = malloc2(size);
  printf("ptr is %p\n", ptr);
  return ptr;
}