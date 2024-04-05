#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

namespace mrkv
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };
  struct DoubleIO
  {
    double& ref;
  };
  struct CharIO
  {
    char& ref;
  };
  struct StringIO
  {
    std::string& ref;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
  private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool compareDataStruct(const DataStruct& a, const DataStruct& b);
  std::string myScientific(double x);
}
#endif
