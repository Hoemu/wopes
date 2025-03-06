#include "log_controller.h"
#include <iostream>

LogController::LogController()
{
    dateLogLongUse = true;
    dateLogTemp = true;
    dataBuffer = new LogDataParam;
    logFile = new LogFile;
}

LogController::~LogController()
{
    delete dataBuffer;
    delete logFile;
}

void LogController::useDateLog(bool var)
{
    dateLogLongUse = var;
}

bool LogController::getDateLog() const
{
    return dateLogLongUse & dateLogTemp;
}

void LogController::push(const MsgData &var)
{
    if (isSettingLogFilePath() == false)
    {
        std::cerr << "[WARNING]:Don't set log path. " << var.msg << std::endl;
        return;
    }

    dataBuffer->push(var);
    logFile->push(var); // 这里是两块不同的内存，控制台日志和文件日志需要分开
}

void LogController::useDateLogTemp(bool var)
{
    dateLogTemp = var;
}

void LogController::setFilePath(list<string> var)
{
    logFile->setFilePath(var);
}

bool LogController::isSettingLogFilePath()
{
    return logFile->logPathVector() > 0;
}
LogDataParam *LogController::getDataBufferObject() const
{
    return dataBuffer;
}
