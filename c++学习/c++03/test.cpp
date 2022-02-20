#include <iostream>
#include <string>
#include <vector>

class Point {
public:
  Point(double x, double y) : x(x), y(y){};
  double x;
  double y;
};

class Graph {
public:
  virtual double getArea() { return 0; };
  std::string idString;
};

class Circle : public Graph {
public:
  Circle(std::string idString, Point centre, double radius)
      : centre(centre), radius(radius) {
    Graph::idString = idString;
  };
  virtual double getArea() { return 3.14 * radius * radius; }

  Point centre;
  double radius;
};

class Polygon : public Graph {
public:
  virtual double getArea() { return 0; };
  std::vector<double> apex;
};

int main() {
  Circle *circle = new Circle("Circle1", Point(1.0, 1.0), 2.0);
  std::cout << "id: " << circle->idString
            << ", Area: " << circle->getArea() << std::endl;
  delete circle;
  return 0;
}
