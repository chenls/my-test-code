#include "MyLib.h"
#include "sec_marker_defs.h"

double MyLib::test2(double x) { return x; }

namespace {
void call_global_array(size_t magic, size_t *begin, size_t *end) {
  if (*begin != magic || *end != magic + 1) {
  }
  typedef void (*func_t)();
  auto fbegin = reinterpret_cast<func_t *>(begin + 1),
       fend = reinterpret_cast<func_t *>(end);
  for (auto i = fbegin; i != fend; ++i) {
    (*i)();
  }
}

void call_global_ctors() {
  call_global_array(23, &megtee_init_array_begin, &megtee_init_array_end);
}

void call_global_dtors() {
  call_global_array(25, &megtee_fini_array_begin, &megtee_fini_array_end);
}
} // namespace

int MyLib::init() {
  call_global_ctors();
  return 0;
}
int MyLib::fini() {
  call_global_dtors();
  return 0;
}