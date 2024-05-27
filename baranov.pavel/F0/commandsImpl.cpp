#include "commandsImpl.hpp"

void baranov::extendDict(dict_t & dict, std::istream & in)
{
  std::string word;
  while (in >> word)
  {
    std::string cleanWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
      char c = word[i];
      if (std::isalpha(c))
      {
        cleanWord += std::tolower(c);
      }
    }
    if (!cleanWord.empty())
    {
      dict[cleanWord]++;
    }
  }
}

bool baranov::countComparator(const std::pair< std::string, size_t > lhs, const std::pair< std::string, size_t > rhs)
{
  return lhs.second < rhs.second;
}

bool baranov::isContains(const dict_t & dict, const std::pair< std::string, size_t > & item)
{
  auto it = dict.find(item.first);
  return it != dict.cend();
}

