#ifndef DSL_SHAPE_H
#define DSL_SHAPE_H

#include <iosfwd>

namespace dsl { // Dummy Shapes Library

class shape {
public:
  shape() noexcept = default; 
  virtual ~shape() noexcept = default;

  shape(int x, int y) noexcept :
    x_{x}, y_{y} {}

  void translate(int dx, int dy) noexcept
    { x_ += dx; y_ += dy; }

  virtual int area() const noexcept = 0;
  virtual void enlarge(int k) noexcept = 0;

  virtual std::string tagname() const = 0;

  friend std::ostream & operator<<(std::ostream & os, const shape & r);
  virtual std::ostream & insert(std::ostream & os) const;

  friend std::istream & operator>>(std::istream & is, shape & r);
  virtual std::istream & extract(std::istream & is);

private:
  int x_=0;
  int y_=0;
};

}

#endif
