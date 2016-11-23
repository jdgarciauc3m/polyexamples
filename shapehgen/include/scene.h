#ifndef DSL_SCENE_H
#define DSL_SCENE_H

#include "shape.h"
#include <iosfwd>
#include <vector>

namespace dsl { // Dummy Shapes Library

class scene {
public:
  void add_shape(shape && s) { shapes_.push_back(std::move(s)); }
  int size() const { return shapes_.size(); }

  long long area() const;
  void move_shapes(int dx, int dy);
  void resize_shapes(int k);

  friend std::ostream & operator<<(std::ostream & os, const scene & s);
  friend std::istream & operator>>(std::istream & is, scene & s);

private:
  using shape_list = std::vector<shape>;

  shape_list shapes_;

};

} // End namespace dsl

#endif
