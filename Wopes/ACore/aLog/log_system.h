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

    void setMessage(const char* format, ...);

    LogController* getControllerObject();

    void setBaseMsg(char* file, const char* functionName, const int& line, const char* logLevel);

protected:
    void log();

    MsgData* data;

    LogController* controller;

private:
    LogSystem();
    ~LogSystem();

    std::condition_variable condConsumer;

    mutex mMutex;

    SpinLock mInputMutex;

    thread* workConsole;
};

#endif // LOG_SYSTEM_H
