#include "Iterators.h"

namespace skor
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    std::string input = "";
    std::getline(in, input, ':');
    in.putback(':');

    size_t start_pos = input.find("e+");
    if (start_pos == std::string::npos)
    {
      start_pos = input.find("e-");
    }
    if (start_pos == std::string::npos)
    {
      start_pos = input.find("E+");
    }
    if (start_pos == std::string::npos)
    {
      start_pos = input.find("E-");
    }

    if (start_pos != std::string::npos)
    {
      dest.ref = std::stod(input);
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, SLLIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    char suffix1 = '0', suffix2 = '0';
    in >> dest.ref >> suffix1;

    if (!in) return in;

    if (suffix1 == 'l' || suffix1 == 'L')
    {
      in >> suffix2;
      if (suffix2 != suffix1)
      {
        in.setstate(std::ios_base::failbit);
      }
    }
    else
    {
      in.setstate(std::ios_base::failbit);
    }

    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using sll = SLLIO;
      using dbl = DoubleIO;
      using str = StringIO;

      in >> sep{ '(' };
      bool flag1 = false, flag2 = false, flag3 = false;
      while (true) {
        if (flag1 && flag2 && flag3) break;
        std::string key = "";
        char c = '0';
        in >> c;
        if (!in) break;

        if (c == ':' && (in >> key))
        {
          if (key == "key1")
          {
            in >> dbl{ input.key1 };
            flag1 = true;
          }
          else if (key == "key2")
          {
            in >> sll{ input.key2 };
            flag2 = true;
          }
          else if (key == "key3")
          {
            in >> str{ input.key3 };
            flag3 = true;
          }
        }
      }
      in >> sep{ ':' } >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << myScientific(src.key1);
    out << ":key2 " << src.key2 << "ll";
    out << ":key3 " << "\"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  bool compareDataStruct(const DataStruct& data1, const DataStruct& data2)
  {
    if (data1.key1 < data2.key1)
    {
      return true;
    }
    else if (data1.key1 == data2.key1)
    {
      if (data1.key2 < data2.key2)
      {
        return true;
      }
      else if (data1.key2 == data2.key2)
      {
        return data1.key3.length() < data2.key3.length();
      }
    }
    return false;
  }

  std::string myScientific(double x)
  {
    std::stringstream ss;
    ss << std::scientific << x;
    std::string out = ss.str();
    size_t i = out.find('e');
    while (out[i - 1] == '0' && out[i - 2] != '.')
    {
      out.erase(i - 1, 1);
      i = out.find('e');
    }
    while (out[i + 2] == '0')
    {
      out.erase(i + 2, 1);
    }
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
