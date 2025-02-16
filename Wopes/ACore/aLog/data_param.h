#ifndef DATAPARAM_H
#define DATAPARAM_H

#include <iostream>
#include <list>
#include <ostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using std::list;
using std::ostream;
using std::queue;
using std::string;
using std::thread;
using std::vector;

/** 日志异常 */
enum class LOG_LEVEL
{
    LOG_INFO = 0,
    LOG_DEBUG,
    LOG_DETUALT,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_OFF,
    LOG_COUNT
};

struct msg_data
{
    string file = "NONE";
    string functionName = "NONE";
    int line = -1;
    string msg;
    char date[24];
    int ms = -1;

    LOG_LEVEL model;
};

class DataParam
{
public:
    queue<msg_data> &getDataBuffer();

    const vector<string> &getLogLevel() const;

    void push(const msg_data &var);

    void pop();

    size_t size();

    msg_data front() const;

private:
    queue<msg_data> data;

    const vector<string> logLevel = { "LOG_INFO", "LOG_DEBUG", "LOG_DETUALT", "LOG_WARN", "LOG_ERROR", "LOG_FATAL", "LOG_OFF", "LOG_COUNT" };
};

#endif // DATAPARAM_H
