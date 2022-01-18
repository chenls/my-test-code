#include <malloc.h>

int main() {
#if 1
  // use for ASAN_OPTIONS=alloc_dealloc_mismatch=1
  //"new" not adapt "free" but "delete"
  int *tempP = new int[10];
  free(tempP);
#endif

#if 0
  // use for ASAN_OPTIONS=detect_leaks=1
  // LOG: not supported on this platform (Android)
  // only adapt Linux ~2021/06/17
  int *tempP = new int[10];
#endif

#if 0
  // use for address check
  // crash and log out
  int *ptr = (int *)malloc(sizeof(int) * 3);
  ptr[4] = 6;
#endif
  return 0;
}