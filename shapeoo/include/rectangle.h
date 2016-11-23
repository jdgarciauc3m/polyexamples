#ifndef DSL_RECTANGLE_H
#define DSL_RECTANGLE_H

#include "shape.h"
#include <iosfwd>
#include <string>

namespace dsl { // Dummy Shapes Library

class rectangle final : public shape {
public:
  rectangle() noexcept = default; 

  rectangle(int x, int y, int w, int h) :
    shape{x,y}, width_{w}, height_{h} {}

  int area() const noexcept override
    { return width_ * height_; }

  void enlarge(int k) noexcept override
    { width_ *= k; height_ *= k; }

  std::string tagname() const override 
    { return "rectangle"; }

  friend std::ostream & operator<<(std::ostream & os, const rectangle & r);
  std::ostream & insert(std::ostream & os) const override;

  friend std::istream & operator>>(std::istream & is, rectangle & r);
  std::istream &  extract(std::istream & is) override;

private:
  int width_=0;
  int height_=0;
};

}

#endif
