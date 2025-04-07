#include "log_controller.h"
#include <iostream>

LogController::LogController()
{
    config.dateLogLongUse = true;
    config.dateLogTemp = true;
    config.isConsoleOutput = true;
    config.isSettingLogFileCurrent = false;
    config.isfoldFilePath = true;
    config.isLogClassify = false;
    dirTool = new ADir;
    logFile = new LogFile;
    dataBuffer = new LogDataParam;
}

LogController::~LogController()
{
    delete logFile;
    delete dirTool;
    delete dataBuffer;
}

void LogController::useDateLog(bool var)
{
    config.dateLogLongUse = var;
}

bool LogController::getDateLog() const
{
    return config.dateLogLongUse & config.dateLogTemp;
}

bool LogController::getConsoleCondition() const
{
    return config.isConsoleOutput;
}

void LogController::setConsoleCondition(const bool &consoleCondition)
{
    config.isConsoleOutput = consoleCondition;
}

void LogController::setFoldFilePath(const bool &var)
{
    config.isfoldFilePath = var;
    // std::cout << "test:" << isfoldFilePath << std::endl;
}

bool LogController::getIsFoldFilePath() const
{
    return config.isfoldFilePath;
}

void LogController::setFileMaxByte(unsigned int max) {}

void LogController::pushChar(MsgData *var)
{
    if (!config.isSettingLogFileCurrent)
    {
        std::cerr << "[WARNING]:Don't set log path. " << var->msg << std::endl;
        return;
    }

    consoleLogPush(var, config.isConsoleOutput);
    logFile->pushChar(var);
}

void LogController::consoleLogPush(MsgData *var, const bool &isPush)
{
    if (!isPush)
    {
        return;
    }
    dataBuffer->pushChar(var);
}

void LogController::useDateLogTemp(bool var)
{
    config.dateLogTemp = var;
}

void LogController::setFilePath(list<string> var)
{
    if (var.size() > 0)
    {
        config.isSettingLogFileCurrent = true;
    }
    else
    {
        config.isSettingLogFileCurrent = false;
    }

    logFile->setFilePath(var);
}

BaseConfigController LogController::queryBaseConfig()
{
    return config;
}

LogDataParam *LogController::getDataBufferObject() const
{
    return dataBuffer;
}

bool LogController::isSettingLogFilePath()
{
    return logFile->logPathVector() > 0;
}
