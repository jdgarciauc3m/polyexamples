#ifndef DSL_CIRCLE_H
#define DSL_CIRCLE_H

#include <iosfwd>
#include <string>

namespace dsl { // Dummy Shapes Library

class circle  {
public:

  circle() noexcept = default; 

  circle(int x, int y, int r) noexcept :
    x_{x}, y_{y},
    radius_{r} 
  {}

  circle(circle &&) noexcept =default;

  std::string tagname() const noexcept
    { return "circle"; }

  int area() const noexcept;

  void translate(int dx, int dy) noexcept
    { x_+=dx; y_+=dy; }

  void enlarge(int k) noexcept
    { radius_ *= k; }

  friend std::ostream & operator<<(std::ostream & os, const circle & r);

  friend std::istream & operator>>(std::istream & is, circle & r);

private:
  int x_=0;
  int y_=0;
  int radius_=0;
};

}

#endif
