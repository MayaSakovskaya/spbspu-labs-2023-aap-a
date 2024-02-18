#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <cstddef>
#include "shape.hpp"
#include "base-types.hpp"

namespace grechishnikov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t* points, size_t size);
    ~Rectangle();
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(const point_t& pos);
    virtual void move(double dx, double dy);
    virtual void scale(double rate);
  private:
    point_t* points_;
    size_t size_;
  };
}

#endif
