#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <list>
#include <string>

using std::list;
using std::string;

class StringUtil
{
public:
    StringUtil();

    static list<string> split(const string &var, const string splitCondition);
};

#endif // STRING_UTIL_H
