#include "log_system.h"
#include <time.h>
#include <iostream>

LogSystem* LogSystem::mInstance = nullptr;

LogSystem* LogSystem::instance()
{
    if (mInstance == nullptr)
    {
        mInstance = new LogSystem;
    }
    return mInstance;
}

void LogSystem::destroy()
{
    if (mInstance != nullptr)
    {
        delete mInstance;
        mInstance = nullptr;
    }
}

void LogSystem::log()
{
    LogDataParam* dataBuffer = controller->getDataBufferObject();

    while (controller->getConsoleCondition())
    {
        std::unique_lock<std::mutex> lock(mMutex);
        while (dataBuffer->size() == 0)
        {
            condConsumer.wait(lock); // 等待缓冲区不空
        }
        std::cout << dataBuffer->frontString() << std::endl;
        dataBuffer->pop();
    }
}

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
    while (dataBuffer->size() != 0)
    {
        if (controller->getConsoleCondition() == false)
        {
            dataBuffer->pop();
        }
    }

    delete workConsole;
    delete controller;
    delete dirTool;
    delete data;
}

void LogSystem::setLogMsg(string file, string functionName, int line)
{
    data->functionName = functionName;

    if (controller->getConsoleCondition() == false)
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
}

void LogSystem::setMsg(std::string msg)
{
    if (msg.empty())
    {
        msg = "Warning:LogNone";
    }

    data->msg = msg;
    controller->push(data);
    condConsumer.notify_one();
}

void LogSystem::setLogModel(LOG_LEVEL model)
{
    data->model = model;
}

void LogSystem::setMsg(int msg)
{
    data->msg = std::to_string(msg);
    controller->push(data);
    condConsumer.notify_one();
}

LogController* LogSystem::getControllerObject() const
{
    return controller;
}
