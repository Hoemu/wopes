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

struct MsgData
{
    MsgData(unsigned int &&dateSize, unsigned int &&baseSize, unsigned int &&msgCharSize);
    ~MsgData();
    string msg;
    char *date;
    char *base;    // TIP 新增
    char *msgChar; // TIP 新增
};

class LogDataParam
{
public:
    LogDataParam();
    ~LogDataParam();

    void pushChar(MsgData *var);

    void popChar();

    size_t sizeChar();

    string frontChar();

private:
    queue<string> dataChar;

    SpinLock mInputMutex;

    mutex mMutex;
};

#endif // LOG_DATAPARAM_H
