#include "circle.h"
#include <iostream>
#include <cmath>

namespace dsl {

int circle::area() const noexcept {
  constexpr double pi = M_PI;
  return int(radius_ * radius_ * pi);
}

std::ostream & operator<<(std::ostream & os, const circle & r) {
  return r.insert(os);
}

std::ostream & circle::insert(std::ostream & os) const {
  shape::insert(os);
  return os << radius_;
}

std::istream & operator>>(std::istream & is, circle & r) {
  return r.extract(is);
}

std::istream & circle::extract(std::istream & is) {
  shape::extract(is);
  return is >> radius_;
}

}
