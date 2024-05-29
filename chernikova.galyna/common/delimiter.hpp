#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace chernikova
{
  struct PunctuationI
  {
    const char expected;
  };

  struct DelimiterI
  {
    const char expected;
    bool upperСase = false;
  };

  struct StringDelimiterI
  {
    const char* exp;
  };

  std::istream& operator>>(std::istream& in, PunctuationI&& exp);
  std::istream& operator>>(std::istream& in, DelimiterI&& exp);
  std::istream& operator>>(std::istream& in, StringDelimiterI&& dest);
}

#endif
