#ifndef NAMESPACE_H
#define NAMESPACE_H

#include "local.h"

namespace kuzn
{
    struct DataStruct
    {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct LabelCharIO
    {
        char& ref;
    };

    struct LongLongIO
    {
        long long& ref;
    };

    struct UnsLongLongIO
    {
        unsigned long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct KeyStringIO
    {
        std::string& ref;
    };

    struct LabelIO
    {
        std::string exp;
    };
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

    bool comparator(const DataStruct& left, const DataStruct& right)
    {
        if (left.key1 == right.key1 && left.key2 == right.key2)
        {
            return left.key3 < right.key3;
        }
        else if (left.key1 == right.key1)
        {
            if (left.key2.first == right.key2.first)
            {
                return left.key2.second < right.key2.second;
            }
            else
            {
                return left.key2.first < right.key2.first;
            }
        }
        else
        {
            return left.key1 < right.key1;
        }
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, LabelCharIO&& dest);
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    std::istream& operator>>(std::istream& in, UnsLongLongIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, KeyStringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}


#endif

