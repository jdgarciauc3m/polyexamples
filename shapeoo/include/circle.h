#ifndef DSL_CIRCLE_H
#define DSL_CIRCLE_H

#include "shape.h"
#include <iosfwd>
#include <string>

namespace dsl { // Dummy Shapes Library

class circle : public shape {
public:

  circle() noexcept = default; 

  circle(int x, int y, int r) noexcept :
    shape{x,y},
    radius_{r} 
  {}

  int area() const noexcept override;

  void enlarge (int k) noexcept override
    { radius_ *= k; }

  std::string tagname() const override
    { return "circle"; }

  friend std::ostream & operator<<(std::ostream & os, const circle & r);
  friend std::istream & operator>>(std::istream & is, circle & r);

protected:
  std::ostream & insert(std::ostream & os) const override;
  std::istream &  extract(std::istream & is) override;

private:
  int radius_=0;
};

}

#endif
