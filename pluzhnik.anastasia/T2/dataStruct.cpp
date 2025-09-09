#include "dataStruct.h"

namespace pluzhnik
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char symbol = '0';
    in >> symbol;
    if (in && (symbol != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DBLIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    char inputFirstPart[100];
    char symbol = '0';
    int dotsCounter = 0;
    int i = 0;
    while (true)
    {
      in >> symbol;
      if (symbol == '.' || isdigit(symbol))
      {
        inputFirstPart[i] = symbol;
        i++;
        if (symbol == '.')
        {
          ++dotsCounter;
        }
      }
      else
      {
        break;
      }
    }

    inputFirstPart[i] = '\0';

    if (dotsCounter != 1)
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }

    if (symbol != 'D' && symbol != 'd')
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }

    dest.ref = std::atof(inputFirstPart);
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
      using dbl = DBLIO;
      using str = StringIO;

      //Ââîäèì ôëàãè äëÿ ïðîâåðêè êîððåêòíîñòè êàæäîãî îòäåëüíîãî êëþ÷à
      in >> sep{ '(' };
      bool flag1 = false, flag2 = false, flag3 = false;
      while (true)
      {
        if (flag1 && flag2 && flag3) break;
        std::string key = "";
        char symbol = '0';
        in >> symbol;

        if (!in) break;

        if (symbol == ':' && (in >> key))
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
    out << ":key1 " << std::fixed << std::setprecision(1) << src.key1 << 'd';
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

  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
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
