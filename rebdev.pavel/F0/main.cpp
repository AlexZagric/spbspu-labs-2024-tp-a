#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <map>
#include <cmath>
#include <functional>

#include "postfix.hpp"
#include "token.hpp"
#include "userCommands.hpp"
#include "standartMathOper.hpp"

int main(int argv, char ** argc)
{
  std::ifstream inFile;
  if (argv == 2)
  {
    inFile.open(argc[1]);
    if (inFile.eof())
    {
      return 0;
    }
  }
  using unary = std::map < std::string, std::function< double(const double &) > >;
  unary unaryCommands;
  unaryCommands["sqrt"] = rebdev::sqrt;
  unaryCommands["sin"] = sin;
  unaryCommands["cos"] = cos;
  double pi = acos(0.0);
  unaryCommands["tg"] = rebdev::tg;
  unaryCommands["ctg"] = rebdev::ctg;
  unaryCommands["abs"] = abs;
  using binary = std::map < std::string, std::function< double(const double &, const double &) > >;
  binary binaryCommands;
  binaryCommands["+"] = rebdev::plus;
  binaryCommands["-"] = rebdev::minus;
  binaryCommands["/"] = rebdev::divides;
  binaryCommands["*"] = rebdev::multiplies;
  binaryCommands["pow"] = pow;
  using userMath = std::map< std::string, std::queue< rebdev::token > >;
  userMath userMathOpers
  using user = std::map < std::string, std::function< void(std::string, unary &, binary &, userMath &) > >;
  user userCommands;
  userCommands["import"] = rebdev::importFile;
  userCommands["export"] = rebdev::exportFile;
  userCommands["add"] = rebdev::add;
  userCommands["replace"] = rebdev::replace;
  std::istream & in = (inFile.is_open() ? inFile : std::cin);
  std::stack< double > resStack;
  while (!in.eof())
  {
    std::string inStr;
    std::getline(in, inStr);
    if (inStr.empty())
    {
      continue;
    }
    std::queue< rebdev::token > postFix;
    try
    {
      rebdev::makePostFix(inStr, postFix, unaryCommands, binaryCommands, userCommands, userMathOpers);
      if (postFix.empty())
      {
        continue;
      }
      double num = rebdev::postFixToResult(postFix);
      resStack.push(num);
    }
    catch (const std::exception & e)
    {
      std::cerr << "Error: " << e.what() << '\n';
    }
  }
  if (!resStack.empty())
  {
    size_t stackSize = (resStack.size() - 1);
    for (size_t i = 0; i < stackSize; ++i)
    {
      std::cout << resStack.top() << ' ';
      resStack.pop();
    }
    std::cout << resStack.top();
  }
  std::cout << '\n';
  return 0;
}
