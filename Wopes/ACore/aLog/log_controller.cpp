#include "log_controller.h"
#include <iostream>

LogController::LogController()
{
    dateLogLongUse = true;
    dateLogTemp = true;
    isConsoleOutput = true;
    isSettingLogFileCurrent = false;
    isfoldFilePath = false;
    dirTool = new ADir;
    logFile = new LogFile;
}

LogController::~LogController()
{
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
    return isConsoleOutput;
}

void LogController::setConsoleCondition(const bool &consoleCondition)
{
    isConsoleOutput = consoleCondition;
}

void LogController::setFoldFilePath(const bool &var)
{
    isfoldFilePath = var;
    // std::cout << "test:" << isfoldFilePath << std::endl;
}

bool LogController::getIsFoldFilePath() const
{
    return isfoldFilePath;
}

void LogController::push(MsgData *var)
{
    if (!isSettingLogFileCurrent)
    {
        std::cerr << "[WARNING]:Don't set log path. " << var->msg << std::endl;
        return;
    }

    consoleLogPush(var, isConsoleOutput);

    logFile->push(var); // 这里是两块不同的内存，控制台日志和文件日志需要分开
}

void LogController::consoleLogPush(MsgData *var, const bool &isPush)
{
    if (!isPush)
    {
        return;
    }
    dataBuffer->push(var);
}

void LogController::useDateLogTemp(bool var)
{
    dateLogTemp = var;
}

void LogController::setFilePath(list<string> var)
{
    if (var.size() > 0)
    {
        isSettingLogFileCurrent = true;
    }
    else
    {
        isSettingLogFileCurrent = false;
    }

    logFile->setFilePath(var);
}

LogDataParam *LogController::getDataBufferObject() const
{
    return dataBuffer;
}

bool LogController::isSettingLogFilePath()
{
    return logFile->logPathVector() > 0;
}
