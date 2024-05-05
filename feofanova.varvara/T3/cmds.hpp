#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include <iomanip>
#include <stream_guard.hpp>
#include "detail.hpp"

namespace feofanova
{
  double feofanova::getArea(const std::vector< Polygon >& data) const;
  bool feofanova::isAreaLess(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const;
  bool feofanova::Perms(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const;
}
#endif
