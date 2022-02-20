#include <iostream>

using namespace std;
class Person {
public:
  Person() { cout << "Person构造" << endl; }
  ~Person() { cout << "Person析构" << endl; }
};

class Teacher : virtual public Person {
public:
  Teacher() { cout << "Teacher构造" << endl; }
  ~Teacher() { cout << "Teacher析构" << endl; }
};

class Student : virtual public Person {
public:
  Student() { cout << "Student构造" << endl; }
  ~Student() { cout << "Student析构" << endl; }
};

class TS : public Teacher, public Student {
public:
  TS() { cout << "TS构造" << endl; }
  ~TS() { cout << "TS析构" << endl; }
};

int main(int argc, char *argv[]) {
  TS ts;
  return 0;
}