#include "Utilities.hpp"

#include <algorithm>
#include <numeric>
#include <functional>


double stepanchenko::areaEven(const std::vector< Polygon >& polygons)
{
  std::vector< Polygon > even_polygons;
  std::vector< double > areas;
  using namespace std::placeholders;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), isEven);
  std::transform(even_polygons.begin(), even_polygons.end(), std::back_inserter(areas), getArea);
  auto area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return area;
}

double stepanchenko::areaOdd(const std::vector< Polygon >& polygons)
{
  std::vector< Polygon > odd_polygons;
  std::vector< double > areas;
  using namespace std::placeholders;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), isOdd);
  std::transform(odd_polygons.begin(), odd_polygons.end(), std::back_inserter(areas), getArea);
  auto area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return area;
}

double stepanchenko::areaMean(const std::vector< Polygon >& polygons)
{
  std::vector< double > areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), getArea);
  auto area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return (area / polygons.size());
}

double stepanchenko::areaNum(const std::vector< Polygon >& polygons, size_t nVertexes)
{
  std::vector< Polygon > fitting_polygons;
  std::vector< double > areas;
  using namespace std::placeholders;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(fitting_polygons), std::bind(hasNumOfVertexes, _1, nVertexes));
  std::transform(fitting_polygons.begin(), fitting_polygons.end(), std::back_inserter(areas), getArea);
  auto area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return area;
}

void stepanchenko::maxArea(std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< int > areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), getArea);
  out << *std::max_element(areas.begin(), areas.end());
}

double stepanchenko::getArea(const Polygon& polygon)
{
  auto t_area = polygon.points.back().x * polygon.points.front().y - polygon.points.back().y * polygon.points.front().x;
  std::vector< double > v1;
  std::vector< double > v2;
  using namespace std::placeholders;
  std::transform(polygon.points.begin(), polygon.points.end() - 1, polygon.points.begin() + 1, std::back_inserter(v1), multiply_points);
  std::transform(polygon.points.begin(), polygon.points.end() - 1, polygon.points.begin() + 1, std::back_inserter(v2), std::bind(multiply_points, _2, _1));
  auto area = std::accumulate(v1.begin(), v1.end(), 0.0) - std::accumulate(v2.begin(), v2.end(), 0.0);
  area += t_area;
  return (std::abs(area) / 2);
}

bool stepanchenko::isEven(const Polygon& polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool stepanchenko::isOdd(const Polygon& polygon)
{
  return (polygon.points.size() % 2 != 0);
}

int stepanchenko::multiply_points(const Point& a, const Point& b)
{
  return (a.x * b.y);
}
bool stepanchenko::hasNumOfVertexes(const Polygon& polygon, const size_t& num)
{
  return polygon.points.size() == num;
}

void stepanchenko::maxArea(std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< int > areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), getArea);
  out << *std::max_element(areas.begin(), areas.end());
}

void stepanchenko::maxVertexes(std::vector< Polygon >& polygons, std::ostream& out)
{
  auto max_vrtx = std::max_element(polygons.begin(), polygons.end(), hasLessVertexes);
  if (max_vrtx == polygons.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  out << max_vrtx->points.size();
}

bool stepanchenko::hasLessVertexes(const Polygon& left, const Polygon& right)
{
  return (left.points.size() < right.points.size());
}
