#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>
#include <numeric>
#include <vector>

#include "polygon.hpp"

double getSumOfAreas(const std::vector< arakelyan::Polygon > &polygons);
bool expectedVertexes(const arakelyan::Polygon &polygon, size_t expectedSize);

void arakelyan::doArea(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  std::vector< Polygon > tempP;

  std::string cmdArg = "";
  in >> cmdArg;

  if (cmdArg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), isEven);
    out << getSumOfAreas(polygons);
  }
  else if (cmdArg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), isOdd);
    out << getSumOfAreas(polygons);
  }
  else if (cmdArg == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::logic_error("<ZERO POLYGONS>");
    }
    out << (getSumOfAreas(polygons) / polygons.size());
  }
  else //num-of-vertexes
  {
    size_t numOfVertexes = 0;
    try
    {
      numOfVertexes = std::stoull(cmdArg);
    }
    catch (const std::invalid_argument &e)
    {
      throw std::invalid_argument("<INVALID ARGUMENT>");
    }
    if (numOfVertexes < 3)
    {
      throw std::logic_error("<VERTEXES < 3 >");
    }

    using namespace std::placeholders;
    auto pr = std::bind(expectedVertexes, _1, numOfVertexes);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), pr);
  }
}

void arakelyan::findMax(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("<ZERO POLYGONS>");
  }
  std::string cmdArg = "";
  in >> cmdArg;
  if (cmdArg == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getArea);
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
  else if (cmdArg == "VERTEXES")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getVertexes);
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
  else
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }
}

void arakelyan::findMin(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("<ZERO POLYGONS>");
  }

  std::string cmdArg = "";
  in >> cmdArg;
  if (cmdArg == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getArea);
    out << *(std::min_element(areas.cbegin(), areas.cend()));
  }
  else if (cmdArg == "VERTEXES")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getVertexes);
    out << *(std::min_element(areas.cbegin(), areas.cend()));
  }
  else
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }
}

void arakelyan::count(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("<ZERO POLYGONS>");
  }

  std::string cmdArg = "";
  in >> cmdArg;

  if (cmdArg == "EVEN")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isEven);

  }
  else if (cmdArg == "ODD")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isOdd);

  }
  else
  {
    int numOfVertexes = 0;
    try
    {
      numOfVertexes = std::stoull(cmdArg);
    }
    catch (const std::invalid_argument &e)
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (numOfVertexes < 3)
    {
      throw std::logic_error("<VERTEXES < 3 >");
    }
    auto pr = std::bind(expectedVertexes, std::placeholders::_1, numOfVertexes);
    out << std::count_if(polygons.cbegin(), polygons.cend(), pr);
  }

}

struct IsEqual
{
  const arakelyan::Polygon &target;

  IsEqual(const arakelyan::Polygon &polygon):
  target(polygon)
  {}

  size_t operator()(const arakelyan::Polygon &polygon) const
  {
    return polygon == target ? 1:0;
  }
};

void arakelyan::maxSeq(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("<ZERO POLYGONS>");
  }

  Polygon pol;
  in >> pol;
  if (!in)
  {
    throw std::invalid_argument("<INVALID POLYGON INPUT>");
  }

  std::vector< size_t > sequence;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(sequence), IsEqual(pol));
  out << *(std::max_element(sequence.cbegin(), sequence.cend()));
}

// void arakelyan::rightShapes(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
// {
//
// }

double getSumOfAreas(const std::vector< arakelyan::Polygon > &polygons)
{
  std::vector< double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getArea);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

bool expectedVertexes(const arakelyan::Polygon &polygon, size_t expectedSize)
{
  return polygon.points.size() == expectedSize;
}
