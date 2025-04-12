#ifndef LOG_DATAPARAM_H
#define LOG_DATAPARAM_H

#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include "../aLock/spin_lock.h"

typedef unsigned int u_int;

using std::list;
using std::mutex;
using std::queue;
using std::string;
using std::thread;
using std::vector;

struct BaseConfigController
{
    bool dateLogTemp;

    bool dateLogLongUse;

    bool isConsoleOutput;

    bool isSettingLogFileCurrent;

    /** 是否折叠文件路径 */
    bool isfoldFilePath;

    /** 是否日志分类 */
    bool isLogClassify;

    bool isExistFilePath;
};

struct MsgData
{
    MsgData(u_int &&dateSize, u_int &&baseSize, u_int &&msgCharSize);
    ~MsgData();
    string msg;

    char *msgData;

    char *date;
    u_int dateLen;

    char *base; // TIP 新增
    u_int baseLen;

    char *msgChar; // TIP 新增
    u_int msgCharLen;

    BaseConfigController baseConfig;
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

    size_t capacity;

    std::atomic<size_t> head { 0 };
    std::atomic<size_t> tail { 0 };

    SpinLock mInputMutex;

    mutex mMutex;

    thread *pushTread;
    thread *popThread;
};

#endif // LOG_DATAPARAM_H
