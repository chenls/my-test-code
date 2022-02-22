#include <chrono> // std::chrono::milliseconds
#include <cstdio>
#include <iostream> // std::cout
#include <mutex>    // std::timed_mutex
#include <thread>   // std::thread

void fireworks(const int *a) {
  *(int *)a = 99;
  printf("a0 = %d\n", *a);
}

int main() {
  int a = 10;
  fireworks(&a);
  printf("a1 = %d\n", a);

  return 0;
}