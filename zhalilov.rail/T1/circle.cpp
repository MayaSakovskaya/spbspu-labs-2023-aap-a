#include "circle.hpp"

#include <stdexcept>

zhalilov::Circle::Circle(double radius, const point_t &center):
  m_frameRect{ radius * 2, radius * 2, center }
{
  if (m_frameRect.width <= 0.0)
  {
    throw std::invalid_argument("circle radius should be more than zero");
  }
}

zhalilov::Circle::~Circle()
{
}

double zhalilov::Circle::getArea() const
{
  return 3.14 * m_frameRect.width * m_frameRect.width / 4.0;
}

zhalilov::rectangle_t zhalilov::Circle::getFrameRect() const
{
  return m_frameRect;
}

void zhalilov::Circle::move(const point_t &point)
{
  m_frameRect.pos = point;
}

void zhalilov::Circle::move(const double dx, const double dy)
{
  m_frameRect.pos = {m_frameRect.pos.x + dx, m_frameRect.pos.y + dy};
}

void zhalilov::Circle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("scaling ratio should be more than zero");
  }
  m_frameRect.width *= ratio;
  m_frameRect.height *= ratio;
}
