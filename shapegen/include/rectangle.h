#ifndef DSL_RECTANGLE_H
#define DSL_RECTANGLE_H

#include <iosfwd>
#include <string>

namespace dsl { // Dummy Shapes Library

class rectangle {
public:

  rectangle() noexcept = default; 

  rectangle(int x, int y, int w, int h) noexcept:
    x_{x}, y_{y},
    width_{w}, height_{h} 
  {}

  std::string tagname() const  
    { return "rectangle"; }

  int area() const noexcept
    { return width_ * height_; }

  void translate(int dx, int dy) noexcept
    { x_+=dx; y_+=dy; }

  void enlarge(int k) noexcept
    { width_ *= k; height_ *= k; }

  friend std::ostream & operator<<(std::ostream & os, const rectangle & r);

  friend std::istream & operator>>(std::istream & is, rectangle & r);

private:
  int x_=0;
  int y_=0;
  int width_=0;
  int height_=0;
};

}

#endif
