#ifndef DSL_SCENE_H
#define DSL_SCENE_H

#include <iosfwd>
#include <vector>

namespace dsl { // Dummy Shapes Library

class rectangle;

class scene {
public:
  void add_shape(const rectangle & r);
  int size() const noexcept { return shapes_.size(); }

  long long area() const noexcept;
  void translate(int dx, int dy) noexcept;
  void enlarge(int k) noexcept;

  friend std::ostream & operator<<(std::ostream & os, const scene & s);
  friend std::istream & operator>>(std::istream & is, scene & s);

private:

  std::vector<rectangle> shapes_;

};

}

#endif
