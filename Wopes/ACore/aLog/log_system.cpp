#include "log_system.h"
#include <time.h>
#include <iostream>
#include <mutex>

LogSystem::LogSystem()
{
    // 设置默认路径
    std::ios::sync_with_stdio(false); // 输出优化
    data = new MsgData;
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
        if (dataBuffer->size() == 0)
        {
            break;
        }
    }

    delete workConsole;
    delete controller;
    delete dirTool;
    delete data;
}

void LogSystem::setLogMsg(string file, string functionName, int line)
{
    mInputMutex.lock();
    data->functionName = functionName;

    if (controller->getIsFoldFilePath() == false)
    {
        data->file = dirTool->getTheFileByThePath(data->file);
    }
    else
    {
        data->file = file;
    }

    data->line = line;

    std::chrono::system_clock::time_point now_ = std::chrono::system_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now_.time_since_epoch()) % 1000;
    time_t now = time(NULL);

    struct tm* local_tm = localtime(&now);

    data->ms = ms.count();
    strftime(data->date, sizeof(data->date), "%Y-%m-%d %H:%M:%S", local_tm);
    mInputMutex.unlock();
}

void LogSystem::setMsg(std::string msg)
{
    mInputMutex.lock();
    if (msg.empty())
    {
        msg = "Warning:LogNone";
    }

    data->msg = msg;
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
}

void LogSystem::setMsg(unsigned int msg)
{
    mInputMutex.lock();
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
}

void LogSystem::setLogModel(LOG_LEVEL model)
{
    data->model = model;
}

void LogSystem::setMsg(int msg)
{
    mInputMutex.lock();
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
}

void LogSystem::setMsg(unsigned long long msg)
{
    mInputMutex.lock();
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
}

void LogSystem::setMsg(long long msg)
{
    mInputMutex.lock();
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
}

void LogSystem::setMsg(unsigned short msg)
{
    mInputMutex.lock();
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
}

void LogSystem::setMsg(short msg)
{
    mInputMutex.lock();
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
    mInputMutex.unlock();
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
        while (controller->getConsoleCondition() && dataBuffer->size() == 0)
        {
            condConsumer.wait(lock); // 等待缓冲区不空
        }
        std::cout << dataBuffer->frontString() << std::endl;
        dataBuffer->pop();
    }
}

void log::setBaseMsg(const string& file, const string& functionName, const int& line)
{
    char buff[512];
    snprintf(buff, sizeof(buff),
        "[%s %s @%d]"
        "\n",
        "[INFO]", __FUNCTION__, __LINE__);
}

void log::setMessage(const char* format, ...) {}
