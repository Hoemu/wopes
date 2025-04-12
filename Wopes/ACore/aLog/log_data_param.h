#ifndef LOG_DATAPARAM_H
#define LOG_DATAPARAM_H

#include "../aLock/spin_lock.h"
#include "./log_config.h"

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

    void releaseChar(char *ptr);
};

class LogDataParam
{
public:
    LogDataParam();
    ~LogDataParam();

    void pushChar(MsgData *var);

    void popChar();

    size_t sizeChar();

    bool isEmpty() noexcept;

    string frontChar();

private:
    queue<string> dataChar;

    size_t capacity;

    bool empty;

    std::atomic<size_t> head { 0 };
    std::atomic<size_t> tail { 0 };

    SpinLock mInputMutex;

    mutex mMutex;

    thread *pushTread;
    thread *popThread;
};

#endif // LOG_DATAPARAM_H
