#ifndef GEOMETRY_FUNC_HPP
#define GEOMETRY_FUNC_HPP

#include <iomanip>
#include "polygon.hpp"

namespace skuratov
{
  bool isEven(const Polygon& poly);
  bool isOdd(const Polygon& poly);
  double countArea(const Polygon& poly);

  double calculateSumOfAreas(double total, const Polygon& poly, std::function< bool(const Polygon& poly)> condition);
  double isMean(double averageArea, const Polygon& poly, size_t numOfPolygons);
  bool isNumOfVertexes(const Polygon& poly, size_t num);

  bool maxAndMinArea(const Polygon& p1, const Polygon& p2);
  bool maxAndMinVertexes(const Polygon& p1, const Polygon& p2);
  void isMaxArea(std::ostream& out, const std::vector< Polygon >& poly);
  void isMaxVertexes(std::ostream& out, const std::vector< Polygon >& poly);
  void isMinArea(std::ostream& out, const std::vector< Polygon >& poly);
  void isMinVertexes(std::ostream& out, const std::vector< Polygon >& poly);

  bool isAreaForLess(const Polygon& polygon, double area);

  int findMinX(const Polygon& poly);
  int findMinY(const Polygon& poly);
  int findMaxX(const Polygon& poly);
  int findMaxY(const Polygon& poly);
  bool compareByX(const Point& p1, const Point& p2);
  bool compareByY(const Point& p1, const Point& p2);
  bool compareMinX(const Polygon& p1, const Polygon& p2);
  bool compareMinY(const Polygon& p1, const Polygon& p2);
  bool compareMaxX(const Polygon& p1, const Polygon& p2);
  bool compareMaxY(const Polygon& p1, const Polygon& p2);
  Polygon createBoundingBox(const std::vector< Polygon >& poly);

  bool straightCorner(const Polygon& poly);
}

#endif
