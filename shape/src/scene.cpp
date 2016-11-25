#include "scene.h"
#include "rectangle.h"
#include <iostream>

namespace dsl { // Dummy Shapes Library

void scene::add_shape(const rectangle & r) {
  shapes_.push_back(r);
}

long long scene::area() const noexcept {
  // transform_reduce(begin(shapes_), end(shapes_).
  //   [](auto x) { return x.area(); }
  //   [](auto x, auto y) { return x+y; });
  long long r = 0;
  for (auto && s : shapes_) {
    r += s.area();
  }
  return r;
}

void scene::translate(int dx, int dy) noexcept {
  for (auto && s : shapes_) {
    s.translate(dx,dy);
  }
}

void scene::enlarge(int k) noexcept {
  for (auto && s : shapes_) {
    s.enlarge(k);
  }
}

std::ostream & operator<<(std::ostream & os, const scene & s) {
  os << "scene\n";
  for (auto && s : s.shapes_) {
    os << "rectangle: " << s << std::endl;
  }
  os << "end-scene";
  return os;
}

std::istream & operator>>(std::istream & is, scene & s) {
  using namespace std;
  string w;
  is >> w;
  if (w!="scene") return is;
  while (is >> w) {
    if (w=="rectangle:") {
      rectangle r;
      is >> r;
      s.add_shape(r);
    }
    else if (w=="end-scene") {
      return is;
    }
    else {
      is.setstate(ios_base::failbit);
      return is;
    }
  }
  return is;
}

} // End namespace dsl
