#include <iostream>

class Base {
public:
  virtual void f(float x) { std::cout << "Base::f(float) " << x << std::endl; }
  void g(float x) { std::cout << "Base::g(float) " << x << std::endl; }
  void h(float x) { std::cout << "Base::h(float) " << x << std::endl; }
};

class Derived : public Base {
public:
  virtual void f(float x) {
    std::cout << "Derived::f(float) " << x << std::endl;
  }
  void g(int x) { std::cout << "Derived::g(int) " << x << std::endl; }
  void h(float x) { std::cout << "Derived::h(float) " << x << std::endl; }
};

int main(void) {
  Derived d;
  Base *base = &d;
  Derived *derived = &d;
  // Good : behavior depends solely on type of the object
  base->f(3.14f); // Derived::f(float) 3.14
  derived->f(3.14f); // Derived::f(float) 3.14
  // Bad : behavior depends on type of the pointer
  base->g(3.14f); // Base::g(float) 3.14
  derived->g(3.14f); // Derived::g(int) 3 (surprise!)
  // Bad : behavior depends on type of the pointer
  base->h(3.14f); // Base::h(float) 3.14 (surprise!)
  derived->h(3.14f); // Derived::h(float) 3.14
}