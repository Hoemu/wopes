#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H

#include <iostream>
#include <mutex>
#include <thread>
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

    void setMsg(std::string msg);

    void setMsg(int msg);

    void setLogModel(LOG_LEVEL model);

    LogController* getControllerObject() const;

protected:
    void log();

private:
    LogSystem();
    ~LogSystem();

    MsgData data;

    static LogSystem* mInstance;

    /** true 为运行状态， false 为关闭状态 */
    bool threadStatus;

    std::mutex mMutex;

    thread* workConsole;

    LogController* controller;
};

#endif // LOG_SYSTEM_H
