#ifndef RGR_UTILITIES_H
#define RGR_UTILITIES_H
#include <iostream>
#include "Dictionary.h"

namespace mrkv
{
  void help(std::ostream& out);
  bool isCleanStr(std::string& str);
  void makeNormal(std::string& str);
  void readTranslations(Dictionary& dic, std::string& key, std::string& input);
}
#endif
