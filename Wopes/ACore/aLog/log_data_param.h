#ifndef LOG_DATAPARAM_H
#define LOG_DATAPARAM_H

#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include "../aLock/spin_lock.h"

using std::list;
using std::mutex;
using std::queue;
using std::string;
using std::thread;
using std::vector;

const char LOG_INFO_CHAR[15] = "LOG_INFO";
const char LOG_DEBUG_CHAR[15] = "LOG_DEBUG";
const char LOG_DETUALT_CHAR[15] = "LOG_DETUALT";
const char LOG_WARN_CHAR[15] = "LOG_WARN";
const char LOG_ERROR_CHAR[15] = "LOG_ERROR";
const char LOG_FATAL_CHAR[15] = "LOG_FATAL";

#define BufferArea 1024

/** 日志异常 */
enum class LOG_LEVEL
{
    LOG_INFO = 0,
    LOG_DEBUG,
    LOG_DETUALT,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
};

struct MsgData
{
    string file = "NONE";
    string functionName = "NONE";
    int line = -1;
    string msg;
    char date[24];
    char base[512];    // TIP 新增
    char msgChar[512]; // TIP 新增
    int ms = -1;

    LOG_LEVEL model;
};

class LogDataParam
{
public:
    LogDataParam();
    ~LogDataParam();

    const vector<string> &getLogLevel() const;

    void push(MsgData *var);

    void pop();

    size_t size();

    string frontString() const;

private:
    queue<string> dataString;

    SpinLock mInputMutex;

    const vector<string> logLevel = { "LOG_INFO", "LOG_DEBUG", "LOG_DETUALT", "LOG_WARN", "LOG_ERROR", "LOG_FATAL" };
};

#endif // LOG_DATAPARAM_H
