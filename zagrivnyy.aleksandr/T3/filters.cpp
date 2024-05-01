#include "filters.hpp"

bool zagrivnyy::checkParity(const Polygon &p, const Parity &parity)
{
  return (p.points.size() % 2 != 0) == parity;
}

double zagrivnyy::addAreaIf(double area, const Polygon &p, bool condition)
{
  if (condition)
  {
    area += p.getArea();
  }
  return area;
}