#include "log_system.h"
#include <time.h>

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
    threadStatus = true;

    while (threadStatus)
    {
        if (dataBuffer->size() > 0)
        {
            mMutex.lock();
            std::cout << dataBuffer->frontString() << std::endl;
            dataBuffer->pop();
            mMutex.unlock();
        }
        else
        {
            // TODO 需要优化
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

LogSystem::LogSystem()
{
    std::ios::sync_with_stdio(false); // 输出优化
    work_console = new std::thread(&LogSystem::log, this);
    controller = new LogController();
    // 设置默认路径
    controller->setFilePath({ "../Input_log", "../Error_log", "../Waring_log" }); // 设置默认路径
}

LogSystem::~LogSystem()
{
    threadStatus = false;
    delete work_console;
    delete controller;
}

void LogSystem::setLogMsg(std::string file, std::string functionName, int line)
{
    data.file = file;
    data.functionName = functionName;
    data.line = line;

    std::chrono::system_clock::time_point now_ = std::chrono::system_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now_.time_since_epoch()) % 1000;
    time_t now = time(NULL);

    struct tm* local_tm = localtime(&now);

    data.ms = ms.count();
    strftime(data.date, sizeof(data.date), "%Y-%m-%d %H:%M:%S", local_tm);
}

void LogSystem::setMsg(std::string msg)
{
    data.msg = msg;
    controller->push(data);
}

void LogSystem::setLogModel(LOG_LEVEL model)
{
    data.model = model;
}

void LogSystem::setMsg(int msg)
{
    data.msg = std::to_string(msg);
    controller->push(data);
}

LogController* LogSystem::getControllerObject() const
{
    return controller;
}
