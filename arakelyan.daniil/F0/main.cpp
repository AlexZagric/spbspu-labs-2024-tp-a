#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <vector>
#include <functional>

#include "cmds.hpp"

int main()
{
  using namespace arakelyan;

  // мапа словарей
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dictionaryOfDictionaries;

  using func = std::function< void(std::istream&, std::ostream&,
                                   std::map< std::string, std::map< std::string, std::vector< std::string > > >&) >;

  std::map< std::string, func > commands;
  {
    using namespace std::placeholders;
    commands["new"] = addDictionary;
    commands["delete"] = deleteDictionary;
    commands["add"] = addWord;
    commands["remove"] = removeWord;
    commands["translate"] = wordTranslations;
    commands["merge"] = mergeDictionaries;
    commands["move"] = moveWords;
    commands["list"] = showAllDictionariesNames;
    commands["size"] = getSizeOfDictionary;
    commands["print"] = printTranslations;
  }

  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = "";
      std::cin >> cmd;
      commands.at(cmd)(std::cin, std::cout, dictionaryOfDictionaries);
    }
    catch (const std::out_of_range &e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
