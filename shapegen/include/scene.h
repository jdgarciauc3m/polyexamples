#ifndef DSL_SCENE_H
#define DSL_SCENE_H

#include <iostream>
#include <vector>
#include <memory>

namespace dsl { // Dummy Shapes Library

template <typename S>
class scene {
public:
  void add_shape(const S & s) { shapes_.push_back(s); }
  int size() const noexcept { return shapes_.size(); }

  long long area() const noexcept;
  void move_shapes(int dx, int dy) noexcept;
  void resize_shapes(int k) noexcept;

  template <typename T>
  friend std::ostream & operator<<(std::ostream & os, const scene<T> & s);

  template <typename T>
  friend std::istream & operator>>(std::istream & is, scene<T> & s);

private:

  std::vector<S> shapes_;

};

template <typename S>
long long scene<S>::area() const noexcept {
  long long r = 0;
  for (auto && s : shapes_) {
    r += s.area();
  }
  return r;
}

template <typename S>
void scene<S>::move_shapes(int dx, int dy) noexcept {
  for (auto && s : shapes_) {
    s.move(dx,dy);
  }
}

template <typename S>
void scene<S>::resize_shapes(int k) noexcept {
  for (auto && s : shapes_) {
    s.resize(k);
  }
}

template <typename S>
std::ostream & operator<<(std::ostream & os, const scene<S> & s) {
  os << "scene\n";
  for (auto && s : s.shapes_) {
    os << s.classname() << ": ";
    os << s << std::endl;
  }
  os << "end-scene";
  return os;
}

template <typename S>
std::istream & operator>>(std::istream & is, scene<S> & s) {
  using namespace std;
  string w;
  is >> w;
  if (w!="scene") return is;
  while (is >> w) {
    S shape;
    if (w == shape.tagname()+":") {
      is >> shape;
      if (is) s.add_shape(shape);
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

#endif
