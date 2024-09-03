#include "dictionary.hpp"

#include <stdexcept>

zagrivnyy::Dictionary::Dictionary():
  dict_()
{
}

void zagrivnyy::Dictionary::add(std::string word, Position pos)
{
  auto it = dict_.find(word);
  if (it != dict_.end())
  {
    it->second.push_back(pos);
  }
  else
  {
    std::vector< Position > positions = {pos};
    dict_.insert(std::make_pair(word, positions));
  }
}

void zagrivnyy::Dictionary::add(std::string word, std::vector< Position > positions)
{
  for (auto pos : positions)
  {
    add(word, pos);
  }
}

void zagrivnyy::Dictionary::remove(std::string word)
{
  dict_.erase(word);
}

std::vector< zagrivnyy::Position > zagrivnyy::Dictionary::get(std::string word)
{
  try
  {
    std::vector< Position > positions = dict_.at(word);
    return positions;
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no such word in dictionary");
  }
}

std::ostream &zagrivnyy::operator<<(std::ostream &out, const Position &pos)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << '(' << pos.row << ';' << pos.col << ')';
  return out;
}
