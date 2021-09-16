#ifndef __T__H_
#define __T__H_

int fib(int n) {
  if (n <= 2) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

#endif