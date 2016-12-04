#ifndef DSL_SCENE_H
#define DSL_SCENE_H

#include "shape.h"
#include <iosfwd>
#include <vector>

namespace dsl { // Dummy Shapes Library

class scene {
public:
  void add_shape(shape && s) { shapes_.push_back(std::move(s)); }
  int size() const noexcept { return shapes_.size(); }

  long long area() const noexcept ;
  void translate(int dx, int dy) noexcept ;
  void enlarge(int k) noexcept;

  friend std::ostream & operator<<(std::ostream & os, const scene & s);
  friend std::istream & operator>>(std::istream & is, scene & s);

private:
  std::vector<shape> shapes_;
};

} // End namespace dsl

#endif
