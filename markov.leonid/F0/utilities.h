#ifndef RGR_UTILITIES_H
#define RGR_UTILITIES_H
#include <iostream>
#include "Dictionary.h"

namespace mrkv
{
  bool isCleanStr(std::string& str);
  void makeNormal(std::string& str);
  bool lineInsert(Dictionary& dict, std::string& line);

  void printTranslations(std::ostream& out, const std::set<std::string>& set);
  void printDictionary(std::ostream& out, Dictionary& dict);
  void help(std::ostream& out);
}
#endif
