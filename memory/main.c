#include "anc_memory_wrapper.h"

int main() {
  void *a = AncMalloc(100);
  AncFree(a);

  AncMemoryWrapperCheck();
  AncMemoryWrapperReleaseChecker();

  void *b = AncMalloc(200);
  AncMemoryWrapperCheck();
  AncFree(b);

  void *c = AncMalloc(200);
  AncFree(c);

  AncMemoryWrapperCheck();
  AncMemoryWrapperReleaseChecker();
  return 0;
}