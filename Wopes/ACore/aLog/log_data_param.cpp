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
        static_assert(true, "data queue char is empty.");
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

MsgData::MsgData(u_int &&dateSize, u_int &&baseSize, u_int &&msgCharSize)
{
    dateLen = dateSize;
    baseLen = baseSize;
    msgCharLen = msgCharSize;
    date = (char *)malloc(dateSize);
    base = (char *)malloc(baseSize);
    msgChar = (char *)malloc(dateSize);
    msgData = (char *)malloc(dateSize + baseSize + dateSize);

    baseConfig.dateLogLongUse = true;
    baseConfig.dateLogTemp = true;
    baseConfig.isConsoleOutput = true;
    baseConfig.isSettingLogFileCurrent = false;
    baseConfig.isfoldFilePath = true;
    baseConfig.isLogClassify = false;
    baseConfig.isExistFilePath = false;
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

    if (msgData != NULL)
    {
        free(msgData);
        msgData = NULL;
    }
}
