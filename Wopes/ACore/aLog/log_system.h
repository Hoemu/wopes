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

    void setMsg(unsigned int msg);

    void setMsg(int msg);

    void setMsg(unsigned long long msg);

    void setMsg(long long msg);

    void setMsg(unsigned short msg);

    void setMsg(short msg);

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

    mutex mMutex;

    SpinLock mInputMutex;

    thread* workConsole;

    LogController* controller;

    ADir* dirTool;
};

#endif // LOG_SYSTEM_H
