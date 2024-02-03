#include "regular.hpp"
#include <iostream>
#include <cmath>

isaychev::Regular::Regular(const point_t & p1, const point_t & p2, const point_t & p3):
  center_(p1),
  closePnt_(p2),
  distPnt_(p3)
{}

double isaychev::Regular::getArea() const
{
  double inRad = 0.0, bottom = 0.0, radX = 0.0, radY = 0.0;
  radX = (distPnt_.x - closePnt_.x) * (distPnt_.x - closePnt_.x);
  radY = (distPnt_.y - closePnt_.y) * (distPnt_.y - closePnt_.y);
  bottom = std::sqrt(radX + radY);
  radX = (center_.x - closePnt_.x) * (center_.x - closePnt_.x);
  radY = (center_.y - closePnt_.y) * (center_.y - closePnt_.y);
  inRad = std::sqrt(radX + radY);
  double numOfSides = std::round(3.1415926535 / std::atan(bottom / inRad));
  return bottom * inRad * numOfSides;
}

isaychev::rectangle_t isaychev::Regular::getFrameRect() const
{
  double radX = 0.0, radY = 0.0;
  radX = (center_.x - closePnt_.x) * (center_.x - closePnt_.x);
  radY = (center_.y - closePnt_.y) * (center_.y - closePnt_.y);
  double leg = std::sqrt(radX + radY);
  radX = (distPnt_.x - center_.x);
  radY = (distPnt_.y - center_.y);
  double outRad = std::sqrt(radX * radX + radY * radY);
  double initXAngle = std::acos(radX / outRad);
  double steerAngle = 2 * std::acos(leg / outRad);
  double numOfSides = std::round(3.1415926535 / std::acos(leg / outRad));
  double minX = 0.0, minY = 0.0, maxX = 0.0, maxY = 0.0;
  minX = maxX = distPnt_.x;
  minY = maxY = distPnt_.y;
  for (double i = 1.0; i < numOfSides; i++)
  {
    double currX = center_.x + outRad * cos(initXAngle + i * steerAngle);
    if (currX < minX)
    {
      minX = currX;
    }
    if (currX > maxX)
    {
      maxX = currX;
    }
    double currY = center_.y + outRad * sin(initXAngle + i * steerAngle);
    if (currY < minY)
    {
      minY = currY;
    }
    if (currY > maxY)
    {
      maxY = currY;
    }
  }
  double width = maxX - minX;
  double height = maxY - minY;
  point_t pos = {minX + (width / 2), minY + (height / 2)};
  return {width, height, pos};
}

void isaychev::Regular::move(const double dX, const double dY)
{
  center_.x += dX;
  closePnt_.x += dX;
  distPnt_.x += dX;
  center_.y += dY;
  closePnt_.y += dY;
  distPnt_.y += dY;
}

void isaychev::Regular::move(const point_t & newPos)
{
  double dX = newPos.x - center_.x;
  closePnt_.x += dX;
  distPnt_.x += dX;
  double dY = newPos.y - center_.y;
  closePnt_.y += dY;
  distPnt_.y += dY;
  center_ = {newPos.x, newPos.y};
}

void isaychev::Regular::scale(const double coeff)
{
  distPnt_.x = center_.x + (distPnt_.x - center_.x) * coeff;
  closePnt_.x = center_.x + (closePnt_.x - center_.x) * coeff;
  distPnt_.y = center_.y + (distPnt_.y - center_.y) * coeff;
  closePnt_.y = center_.y + (closePnt_.y - center_.y) * coeff;
}
