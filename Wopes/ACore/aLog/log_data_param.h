#ifndef LOG_DATAPARAM_H
#define LOG_DATAPARAM_H

#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using std::list;
using std::mutex;
using std::queue;
using std::string;
using std::thread;
using std::vector;

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

    void pushString(const string &str);

    void pop();

    size_t size();

    string frontString() const;

private:
    queue<string> dataString;

    mutex mInputMutex;

    const vector<string> logLevel = { "LOG_INFO", "LOG_DEBUG", "LOG_DETUALT", "LOG_WARN", "LOG_ERROR", "LOG_FATAL" };
};

#endif // LOG_DATAPARAM_H
