#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iostream>
#include <list>
#include <string>

using std::list;
using std::string;

class StringUtil
{
public:
    StringUtil();

    static list<string> split(const string &var, const string &splitCondition, const bool &isFilePath = false);

    /**
     * @brief combination 组合字符串
     * @param split 目标字符串
     * @param splitCondition [字符串链表]每个字符串最后一位[新增字符串]名称
     * @param endAddtion [字符串链表]最后一个字符串是否需要添加[新增字符串]
     * @return string 返回一个[字符串]
     */
    static string combination(const list<string> &stringList, const string &addtionString, const bool &endAddtion = false);
};

#endif // STRING_UTIL_H
