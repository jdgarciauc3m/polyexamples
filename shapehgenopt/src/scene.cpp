#include "scene.h"
#include "rectangle.h"
#include "circle.h"
#include <iostream>
#include <stdexcept>

namespace dsl {

long long scene::area() const noexcept {
  long long r = 0;
  for (auto && s : shapes_) {
    r += s.area();
  }
  return r;
}

void scene::move_shapes(int dx, int dy) noexcept {
  for (auto && s : shapes_) {
    s.move(dx,dy);
  }
}

void scene::resize_shapes(int k) noexcept {
  for (auto && s : shapes_) {
    s.resize(k);
  }
}

std::ostream & operator<<(std::ostream & os, const scene & s) {
  os << "scene\n";
  for (auto && s : s.shapes_) {
    os << s.classname() << ": ";
    os << s << std::endl;
  }
  os << "end-scene";
  return os;
}

namespace {

shape make_shape(const std::string & cname) {
  using namespace std;
  if (cname=="rectangle:") return dsl::shape::make<dsl::rectangle>();
  else if (cname=="circle:") return dsl::shape::make<dsl::circle>();
  throw invalid_argument{"Unexpected shape name: " + cname};
}

}


std::istream & operator>>(std::istream & is, scene & s) {
  using namespace std;
  string w;
  is >> w;
  if (w!="scene") return is;
  while (is >> w) {
    try {
      auto sh = make_shape(w);
      is >> sh;
      if (is) s.add_shape(move(sh));
    }
    catch(...) {
      if (w=="end-scene") {
        return is;
      }
      else {
        is.setstate(ios_base::failbit);
        return is;
      }
    }
  }
  return is;
}

}
