#ifndef __T__H_
#define __T__H_

class T {

public:
  T() {}
  ~T() {}

  int fib(int n) {
    if (n <= 2) {
      return n;
    }

    return fib(n - 1) + fib(n - 2);
  }
};

template <typename T> T sum(T *arr, int len) {
  T result = T(0);
  for (int i = 0; i < len; i++) {
    result += arr[i];
  }

  return result;
}

#endif