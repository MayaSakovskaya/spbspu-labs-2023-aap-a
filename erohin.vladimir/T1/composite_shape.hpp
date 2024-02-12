#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <cstddef>
#include "shape.hpp"

namespace erohin
{
  class CompositeShape
  {
  public:
    CompositeShape();
    CompositeShape(CompositeShape&& rhs) noexcept;
    ~CompositeShape();
    CompositeShape& operator=(CompositeShape&& rhs) noexcept;
    Shape& operator[](size_t index);
    const Shape& operator[](size_t index) const;
    Shape& at(size_t index);
    const Shape& at(size_t index) const;
    void push(const Shape& shape);
    void push(Shape&& shape);
    void pop();
    bool empty() const;
    size_t size() const;
  private:
    size_t capacity_;
    size_t size_;
    Shape** shape_;
    void swap(CompositeShape& rhs);
    void resize(size_t length);
  };
}

#endif
