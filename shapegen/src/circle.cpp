#include "circle.h"
#include <iostream>
#include <cmath>

namespace dsl {

int circle::area() const noexcept {
  constexpr double pi = M_PI;
  return int(radius_ * radius_ * pi);
}

std::ostream & operator<<(std::ostream & os, const circle & r) {
  return os << r.x_ << ' ' << r.y_ << ' ' << r.radius_;
}

std::istream & operator>>(std::istream & is, circle & r) {
  return is >> r.x_ >> r.y_ >> r.radius_;
}

}
