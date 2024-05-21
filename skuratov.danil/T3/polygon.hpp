#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace skuratov
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& diff) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    int getCorners() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct �alculateArea
  {
    Point point1;
    double operator()(double res, const Point& point2, const Point& point3);
  };

  struct �alculateCorners
  {
    Point point1, point2;
    bool operator()(const Point& point3);
  };
}

#endif
