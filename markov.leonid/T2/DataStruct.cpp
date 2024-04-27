#include "DataStruct.h"

namespace mrkv
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
    in >> input;
    if ((input[1] == '.' && (input[4] == 'e' || input[4] == 'E')
      && (input[5] == '+' || input[5] == '-'))
      || (input[1] == '.' && (input[3] == 'e' || input[3] == 'E')
        && (input[4] == '+' || input[4] == '-')))
    {
      if (input[input.length() - 2] == ':')
      {
        in.putback(')');
        in.putback(':');
        input.erase(input.length() - 2, input.length());
        dest.ref = std::stod(input);
      }
      else
      {
        in.putback(*input.rbegin());
        in.putback('y');
        in.putback('e');
        in.putback('k');
        in.putback(':');
        input.erase(input.length() - 5, input.length());
        dest.ref = std::stod(input);
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, CharIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char open_quote = '0';
    char close_quote = '0';
    in >> open_quote >> dest.ref >> close_quote;
    if (open_quote != '\'' || close_quote != '\'' || !in)
    {
      in.setstate(std::ios::failbit);
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
      using dbl = DoubleIO;
      using chr = CharIO;
      using str = StringIO;

      in >> sep{ '(' };
      bool flag1 = false, flag2 = false, flag3 = false;
      while (true)
      {
        if (flag1 && flag2 && flag3)
        {
          break;
        }
        std::string key = "";
        char c = '0';
        in >> c;
        if (!in)
        {
          break;
        }

        if (c == ':' && (in >> key))
        {
          if (key == "key1")
          {
            in >> dbl{ input.key1 };
            flag1 = true;
          }
          else if (key == "key2")
          {
            in >> chr{ input.key2 };
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

  std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << myScientific(src.key1) << ":key2 '" << src.key2 << "':key3 \"" << src.key3 << "\":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}
<<<<<<< HEAD
=======

>>>>>>> master
  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

  bool compareDataStruct(const DataStruct& a, const DataStruct& b)
  {
    if (a.key1 != b.key1)
    {
      return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2)
    {
      return a.key2 < b.key2;
    }
    else
    {
      return a.key3.length() < b.key3.length();
    }
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
}
