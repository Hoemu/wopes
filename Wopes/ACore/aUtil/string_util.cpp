#include "string_util.h"

StringUtil::StringUtil() {}

list<string> StringUtil::split(const string &var, const string &splitCondition, const bool &isFilePath)
{
    list<string> listStr;
    int dirIndex = 0;
    int preIndex = 0;
    int len = 0;

    while (dirIndex < var.size())
    {
        int pos = var.find_first_of(splitCondition, dirIndex);
        dirIndex = splitCondition.size() + pos;
        len = pos - preIndex;
        listStr.push_back(var.substr(preIndex, len));
        preIndex = pos + 1;

        if (pos == string::npos)
        {
            break;
        }
    }

    return listStr;
}

string StringUtil::combination(const list<string> &stringList, const string &addtionString)
{
    string backString;
    for (const string &var : stringList)
    {
        backString = backString + var + addtionString;
    }
    return backString;
}
