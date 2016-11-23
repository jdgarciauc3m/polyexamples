#ifndef DSL_SCENE_H
#define DSL_SCENE_H

#include <iosfwd>
#include <vector>
#include <memory>

namespace dsl { // Dummy Shapes Library

class shape;

class scene {
public:
  void add_shape(std::shared_ptr<shape> && s) { shapes_.push_back(s); }
  int size() const noexcept { return shapes_.size(); }

  long long area() const noexcept;
  void translate(int dx, int dy) noexcept;
  void enlarge(int k) noexcept;

  friend std::ostream & operator<<(std::ostream & os, const scene & s);
  friend std::istream & operator>>(std::istream & is, scene & s);

private:
  std::vector<std::shared_ptr<shape>> shapes_;
};

}

#endif
