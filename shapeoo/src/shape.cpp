#include "rectangle.h"
#include <iostream>

namespace dsl {

std::ostream & shape::insert(std::ostream & os) const {
  return os << x_ << ' ' << y_ << ' ';
}

std::istream & shape::extract(std::istream & is) {
  return is >> x_ >> y_;
}

std::ostream & operator<<(std::ostream & os, const shape & r) {
  return r.insert(os);
}

std::istream & operator>>(std::istream & is, shape & r) {
  return r.extract(is);
}

}
