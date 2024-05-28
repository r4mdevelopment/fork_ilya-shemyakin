#include <algorithm>
#include <sstream>
#include "utilities.h"

namespace mrkv
{
  void help(std::ostream& out)
  {
    out << "Commands info: \n";
    out << "INPUT <filename.txt> - Get the dictionary from file.\n";
    out << "OUTPUT <filename.txt> - Put the dictionary into file.\n";
    out << "ADD <ENG_word> - Add a word to the dictionary.\n";
    out << "DELETE <ENG_word> - Delete a word from the dictionary.\n";
    out << "FIND <ENG_word> - Find the word and print it.\n";
    out << "PRINT - Print whole dictionary.\n";
    out << "STAT - Get dictionary info.\n";
    out << "HELP - For help.\n";
  }

  bool isCleanStr(std::string& str)
  {
    return (str.find_first_of("0123456789~!@#$;%:^&?*()-_+=[]{}|/'.,\n") == std::string::npos);
  }

  void makeNormal(std::string& str)
  {
    size_t start = str.find_first_not_of(" ");
    if (start == std::string::npos)
    {
      str.clear();
      return;
    }
    size_t end = str.find_last_not_of(" ");
    str = str.substr(start, end - start + 1);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  }

  void readTranslations(Dictionary& dic, std::string& key, std::string& input)
  {
    std::istringstream iss(input);
    std::string translation = "";
    while (std::getline(iss, translation, ','))
    {
      dic.add(key, translation);
    }
  }
}
