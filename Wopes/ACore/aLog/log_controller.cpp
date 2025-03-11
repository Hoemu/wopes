#include "log_controller.h"
#include <iostream>

LogController::LogController()
{
    dateLogLongUse = true;
    dateLogTemp = true;
    consoleThread = true;
    isfoldFilePath = false;
    dirTool = new ADir;
    dataBuffer = new LogDataParam;
    logFile = new LogFile;
}

LogController::~LogController()
{
    consoleThread = false;
    delete dataBuffer;
    delete logFile;
    delete dirTool;
}

void LogController::useDateLog(bool var)
{
    dateLogLongUse = var;
}

bool LogController::getDateLog() const
{
    return dateLogLongUse & dateLogTemp;
}

bool LogController::getConsoleCondition() const
{
    return consoleThread;
}

void LogController::setConsoleCondition(const bool &condition)
{
    consoleThread = condition;
}

void LogController::setFoldFilePath(const bool &var)
{
    isfoldFilePath = var;
    // std::cout << "test:" << isfoldFilePath << std::endl;
}

void LogController::push(MsgData *var)
{
    if (isSettingLogFilePath() == false)
    {
        std::cerr << "[WARNING]:Don't set log path. " << var->msg << std::endl;
        return;
    }

    if (consoleThread == false)
    {
        dataBuffer->push(var);
    }
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
