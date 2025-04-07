#include "log_data_param.h"
#include <iostream>

LogDataParam::LogDataParam() {}

LogDataParam::~LogDataParam()
{
    while (!dataChar.empty())
    {
        dataChar.pop();
    }
}

void LogDataParam::pushChar(MsgData *var)
{
    mInputMutex.lock();
    dataChar.push(var->msg);
    mInputMutex.unlock();
}

void LogDataParam::popChar()
{
    mInputMutex.lock();
    if (dataChar.empty())
    {
        std::cerr << "Data char queue is empty." << std::endl;
        return;
    }

    dataChar.pop();
    mInputMutex.unlock();
}

size_t LogDataParam::sizeChar()
{
    SpinLockGuard guardLock(mInputMutex);
    return dataChar.size();
}

string LogDataParam::frontChar()
{
    SpinLockGuard guardLock(mInputMutex);
    return dataChar.front();
}
