#include "rectangle.h"
#include <iostream>

namespace dsl {

std::ostream & operator<<(std::ostream & os, const rectangle & r) {
  return r.insert(os);
}

std::ostream & rectangle::insert(std::ostream & os) const {
  shape::insert(os);
  return os << width_ << " " << height_;
}

std::istream & operator>>(std::istream & is, rectangle & r) {
  return r.extract(is);
}

std::istream & rectangle::extract(std::istream & is) {
  shape::extract(is);
  return is >> width_ >> height_;
}

}
