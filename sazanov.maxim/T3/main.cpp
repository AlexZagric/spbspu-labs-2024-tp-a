#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <fstream>
#include <algorithm>
#include "Polygon.hpp"
#include "CommandFacade.hpp"

using namespace sazanov;
int main(int count, char* args[])
{
 if (count < 2)
  {
    std::cerr << "missed filename argument\n";
    return 1;
  }
  std::ifstream file(args[1]);
  if (!file.is_open())
  {
    std::cerr << "cant open file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  std::copy_if(input_it_t(file), input_it_t(), std::back_inserter(polygons), isValidPolygon);
  file.close();

  CommandFacade facade(polygons);
  while (!std::cin.eof())
  {
    facade.nextCommand(std::cin, std::cout);
    if (!std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << '\n';
    }
  }
  return 0;
}
