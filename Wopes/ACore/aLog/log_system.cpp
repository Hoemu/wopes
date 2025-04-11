#include "log_system.h"
#include <time.h>
#include <iostream>
#include <mutex>

LogSystem::LogSystem()
{
    // 设置默认路径
    std::ios::sync_with_stdio(false); // 输出优化
    data = new MsgData(256, 512, 512);
    controller = new LogController();
    dirTool = new ADir;
    workConsole = new std::thread(&LogSystem::log, this);
    workConsole->detach();
}

LogSystem::~LogSystem()
{
    LogDataParam* dataBuffer = controller->getDataBufferObject();
    while (controller->getConsoleCondition())
    {
        if (controller->getConsoleCondition() == false)
        {
            condConsumer.notify_one();
        }
        if (dataBuffer->sizeChar() == 0)
        {
            break;
        }
    }

    delete workConsole;
    delete controller;
    delete dirTool;
    delete data;
}

LogController* LogSystem::getControllerObject() const
{
    return controller;
}

void LogSystem::log()
{
    LogDataParam* dataBuffer = controller->getDataBufferObject();

    while (controller->getConsoleCondition())
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (dataBuffer == nullptr)
        {
            continue;
        }
        while (controller->getConsoleCondition() && dataBuffer->sizeChar() == 0)
        {
            condConsumer.wait(lock); // 等待缓冲区不空
        }
        std::cout << dataBuffer->frontChar() << std::endl;
        dataBuffer->popChar();
    }
}

void LogSystem::setBaseMsg(char* file, const char* functionName, const int& line, const char* logLevel)
{
    mMutex.lock();
    // mInputMutex.lock();
    if (data->IsFoldFilePath == false)
    {
        if (controller->getIsFoldFilePath() == true)
        {
            file = "NONE";
            data->IsFoldFilePath = true;
        }
    }
    else
    {
        file = "NONE";
    }

    std::chrono::system_clock::time_point now_ = std::chrono::system_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now_.time_since_epoch()) % 1000;
    time_t now = time(NULL);
    struct tm* local_tm = localtime(&now);

    strftime(data->date, data->dateLen, "[%Y-%m-%d %H:%M:%S", local_tm);
    snprintf(data->base, data->baseLen, ":%d] [%s] %s:(%s)@%d ", ms.count(), logLevel, file, functionName, line);
    // mInputMutex.unlock();
    mMutex.unlock();
}

void LogSystem::setMessage(const char* format, ...)
{
    mMutex.lock();
    // mInputMutex.lock();
    __builtin_va_list local_argv;
    __builtin_va_start(local_argv, format);
    __mingw_vsnprintf(data->msgChar, data->msgCharLen, format, local_argv); // 固定大小？
    __builtin_va_end(local_argv);

    // std::cout << "print:" << data->date << data->base << data->msgChar << std::endl;
    data->msg = data->date;
    data->msg = data->msg + data->base;
    data->msg = data->msg + data->msgChar;

    controller->pushChar(data);
    condConsumer.notify_one();
    // mInputMutex.unlock();
    mMutex.unlock();
}
