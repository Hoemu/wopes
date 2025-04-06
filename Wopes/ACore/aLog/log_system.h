#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H

#include <condition_variable>
#include "../aUtil/internal_singleton.h"
#include "log_controller.h"
#include "log_data_param.h"

class ACORE_EXPORT LogSystem : public InternalSingleton<LogSystem>
{
public:
    friend class InternalSingleton<LogSystem>;
    void setLogMsg(std::string file, std::string functionName, int line);

    void setMsg(string msg);

    void setLogModel(LOG_LEVEL model);

    LogController* getControllerObject() const;

protected:
    void log();

private:
    LogSystem();
    ~LogSystem();

    MsgData* data;

    std::condition_variable condConsumer;

    mutex mMutex;

    SpinLock mInputMutex;

    thread* workConsole;

    LogController* controller;

    ADir* dirTool;
};

class ACORE_EXPORT log : public LogSystem
{
public:
    friend class InternalSingleton<LogSystem>;

    void setBaseMsg(const string& file, const string& functionName, const int& line);

    void setMessage(const char* format, ...);

private:
    char msg[512];
};

#endif // LOG_SYSTEM_H
