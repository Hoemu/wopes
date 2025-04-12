#include "log_data_param.h"
#include <iostream>

LogDataParam::LogDataParam()
{
    // pushTread = new thread(&LogDataParam::pushChar, this, nullptr);
    // popThread = new thread(&LogDataParam::popChar, this);
    dataChar = {};

    empty = true;
}

LogDataParam::~LogDataParam()
{
    while (!dataChar.empty())
    {
        dataChar.pop();
    }
}

void LogDataParam::pushChar(MsgData *var)
{
    if (var == nullptr)
    {
        return;
    }
    mInputMutex.lock();
    dataChar.push(var->msg);
    mInputMutex.unlock();
}

void LogDataParam::popChar()
{
    SpinLockGuard guard(mInputMutex);
    // mInputMutex.lock();
    if (dataChar.empty())
    {
        std::cerr << "data queue char is empty." << std::endl;
        // static_assert(true, "data queue char is empty.");

        return;
    }

    dataChar.pop();
}

size_t LogDataParam::sizeChar()
{
    // SpinLockGuard guardLock(mInputMutex);
    if (dataChar.empty())
    {
        return 0;
    }
    return dataChar.size();
}

bool LogDataParam::isEmpty() noexcept
{
    return dataChar.empty();
}

string LogDataParam::frontChar()
{
    // SpinLockGuard guardLock(mInputMutex);
    return dataChar.front();
}

MsgData::MsgData(u_int &&dateSize, u_int &&baseSize, u_int &&msgCharSize)
{
    dateLen = dateSize;
    baseLen = baseSize;
    msgCharLen = msgCharSize;
    date = (char *)malloc(dateSize);
    base = (char *)malloc(baseSize);
    msgChar = (char *)malloc(dateSize);
    msgData = (char *)malloc(dateSize + baseSize + dateSize);
}

MsgData::~MsgData()
{
    releaseChar(date);
    releaseChar(base);
    releaseChar(msgChar);
    releaseChar(msgData);
}

void MsgData::releaseChar(char *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}
