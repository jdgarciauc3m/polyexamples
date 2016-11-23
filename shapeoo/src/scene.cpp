#include "scene.h"
#include "rectangle.h"
#include "circle.h"
#include <iostream>
#include <string>

namespace dsl { // Dummy Shapes Library

long long scene::area() const noexcept {
  long r = 0;
  for (auto && s : shapes_) {
    r += s->area();
  }
  return r;
}

void scene::translate(int dx, int dy) noexcept {
  for (auto && s : shapes_) {
    s->translate(dx,dy);
  }
}

void scene::enlarge(int k) noexcept {
  for (auto && s : shapes_) {
    s->enlarge(k);
  }
}

std::ostream & operator<<(std::ostream & os, const scene & s) {
  os << "scene\n";
  for (auto && s : s.shapes_) {
    os << s->tagname() << ": ";
    s->insert(os); // Polymorphic write
    os << std::endl;
  }
  os << "end-scene";
  return os;
}

namespace { // Anonymous namespace

std::shared_ptr<shape> make_shape(const std::string & cname) {
  using namespace std;
  shared_ptr<shape> p = nullptr;
  if (cname=="rectangle:") p = make_shared<rectangle>();
  else if (cname=="circle:") p = make_shared<circle>();
  return p;
}

}

std::istream & operator>>(std::istream & is, scene & s) {
  using namespace std;
  string w;
  is >> w;
  if (w!="scene") return is;
  while (is >> w) {
    auto sh = make_shape(w);
    if (sh) {
      is >> *sh;
      s.add_shape(std::move(sh));
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
