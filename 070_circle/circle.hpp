#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & center, const double radius);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif  // CIRCLE_HPP
