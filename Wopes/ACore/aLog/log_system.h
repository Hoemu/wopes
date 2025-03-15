#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H

#include <condition_variable>
#include <mutex>
#include "log_controller.h"
#include "log_data_param.h"

class LogBaseSystem
{
public:
};

class ACORE_EXPORT LogSystem : public LogBaseSystem
{
public:
    static LogSystem* instance();

    static void destroy();

    void setLogMsg(std::string file, std::string functionName, int line);

    void setMsg(string msg);

    void setMsg(int msg);

    void setLogModel(LOG_LEVEL model);

    LogController* getControllerObject() const;

protected:
    void log();

private:
    LogSystem();
    ~LogSystem();

    MsgData* data;

    static LogSystem* mInstance;

    std::condition_variable condConsumer;

    std::condition_variable condProducer;

    std::mutex mMutex;

    thread* workConsole;

    LogController* controller;

    ADir* dirTool;
};

#endif // LOG_SYSTEM_H
