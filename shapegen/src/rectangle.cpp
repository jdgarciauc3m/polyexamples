#include "rectangle.h"
#include <iostream>

namespace dsl {

std::ostream & operator<<(std::ostream & os, const rectangle & r) {
  return os << r.x_ << ' ' << r.y_ << ' ' << r.width_ << ' ' << r.height_;
}

std::istream & operator>>(std::istream & is, rectangle & r) {
  return is >> r.x_ >> r.y_ >> r.width_ >> r.height_;
}

}
