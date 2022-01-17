#include "anc_log.h"
#include "anc_memory_wrapper.h"

#define LOG_TAG "[ANC_MAIN]"

int main() {
  void *a = AncMalloc(100);
  AncFree(a);

  char p[5] = {0};
  int index = 5;
  p[index] = 5;

  // AncMemoryWrapperCheck();
  // AncMemoryWrapperReleaseChecker();

  void *b = AncMalloc(200);
  AncMemoryWrapperCheck();
  AncFree(b);

  void *c = AncMalloc(200);
  AncFree(c);

  int ret = AncMemoryWrapperCheck();
  ANC_LOGD("ret = %d", ret);
  AncMemoryWrapperReleaseChecker();
  return ret;
}