#ifndef NAMESPACE_H
#define NAMESPACE_H

#include "local.h"

namespace hismatulin
{
  // ULL LIT
  // CMP LSP

  struct DataStruct
  {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  // COMPLEX&
  struct CMPDouble_ST
  {
    std::complex<double>& ref;
  };

  // ULL&
  struct ULL_ST
  {
    unsigned long long& ref;
  };

  // DOUBLE&
  struct Double_ST
  {
    double& num;
  };

  // STRING&
  struct String_ST
  {
    std::string& ref;
  };

  // STRING
  struct Label_ST
  {
    std::string exp;
  };

  // scope guard 
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, CMPDouble_ST&& dest);
  std::istream& operator>>(std::istream& in, ULL_ST&& dest);
  std::istream& operator>>(std::istream& in, String_ST&& dest);
  std::istream& operator>>(std::istream& in, Label_ST&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

  bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}

#endif
