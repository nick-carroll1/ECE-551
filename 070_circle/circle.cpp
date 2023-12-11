#include "circle.hpp"

#include <cmath>

Circle::Circle(const Point & center, const double radius) :
    center(center), radius(radius) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.distanceFrom(otherCircle.center);

  if (distance >= (radius + otherCircle.radius))
    return 0.0;

  if (distance <= std::abs(radius - otherCircle.radius)) {
    double smallerRadius = (radius < otherCircle.radius) ? radius : otherCircle.radius;
    return M_PI * smallerRadius * smallerRadius;
  }

  double angle1 = 2.0 * std::acos((radius * radius + distance * distance -
                                   otherCircle.radius * otherCircle.radius) /
                                  (2.0 * radius * distance));
  double angle2 = 2.0 * std::acos((otherCircle.radius * otherCircle.radius +
                                   distance * distance - radius * radius) /
                                  (2.0 * otherCircle.radius * distance));
  double area1 = 0.5 * radius * radius * (angle1 - sin(angle1));
  double area2 = 0.5 * otherCircle.radius * otherCircle.radius * (angle2 - sin(angle2));

  return area1 + area2;
}
