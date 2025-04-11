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
    mMutex.lock();
    // mInputMutex.lock();
    dataChar.push(var->msg);
    // mInputMutex.unlock();
    mMutex.unlock();
}

void LogDataParam::popChar()
{
    mMutex.lock();
    // mInputMutex.lock();
    if (dataChar.empty())
    {
        std::cerr << "Data char queue is empty." << std::endl;
        return;
    }

    dataChar.pop();
    // mInputMutex.unlock();
    mMutex.unlock();
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

MsgData::MsgData(unsigned int &&dateSize, unsigned int &&baseSize, unsigned int &&msgCharSize)
{
    date = (char *)malloc(sizeof(dateSize));
    base = (char *)malloc(sizeof(baseSize));
    msgChar = (char *)malloc(sizeof(dateSize));
}

MsgData::~MsgData()
{
    if (date != NULL)
    {
        free(date);
        date = NULL;
    }

    if (base != NULL)
    {
        free(base);
        base = NULL;
    }

    if (msgChar != NULL)
    {
        free(msgChar);
        msgChar = NULL;
    }
}
