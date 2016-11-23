#ifndef DSL_CIRCLE_H
#define DSL_CIRCLE_H

#include <iosfwd>
#include <string>

namespace dsl { // Dummy Shapes Library

class circle  {
public:

  circle() = default; 

  circle(int x, int y, int r) :
    x_{x}, y_{y},
    radius_{r} 
  {}

  int area() const;

  void move(int dx, int dy)
    { x_+=dx; y_+=dy; }

  void resize(int k) 
    { radius_ *= k; }

  std::string classname() const 
    { return "circle"; }

  friend std::ostream & operator<<(std::ostream & os, const circle & r);

  friend std::istream & operator>>(std::istream & is, circle & r);

private:
  int x_=0;
  int y_=0;
  int radius_=0;
};

}

#endif
