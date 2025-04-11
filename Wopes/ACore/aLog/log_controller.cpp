#include "log_controller.h"
#include <iostream>

LogController::LogController()
{
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
    confData->baseConfig.dateLogLongUse = var;
}

void LogController::setConfData(MsgData *var)
{
    std::cout << "set conf data is success." << std::endl;
    confData = var;
}

bool LogController::getDateLog() const
{
    return confData->baseConfig.dateLogLongUse & confData->baseConfig.dateLogTemp;
}

bool LogController::getConsoleCondition() const
{
    return confData->baseConfig.isConsoleOutput;
}

void LogController::setConsoleCondition(const bool &consoleCondition)
{
    confData->baseConfig.isConsoleOutput = consoleCondition;
}

void LogController::setFoldFilePath(const bool &var)
{
    confData->baseConfig.isfoldFilePath = var;
    // std::cout << "test:" << isfoldFilePath << std::endl;
}

bool LogController::getIsFoldFilePath() const
{
    return confData->baseConfig.isfoldFilePath;
}

void LogController::setFileMaxByte(unsigned int max) {}

void LogController::pushChar(MsgData *var)
{
    if (!confData->baseConfig.isExistFilePath)
    {
        std::cerr << "[WARNING]:Don't set log path: " << var->msg << std::endl;
        return;
    }

    consoleLogPush(var, confData->baseConfig.isConsoleOutput);
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
    confData->baseConfig.dateLogTemp = var;
}

void LogController::setFilePath(list<string> var)
{
    if (var.size() > 0)
    {
        confData->baseConfig.isExistFilePath = true;
    }
    else
    {
        confData->baseConfig.isExistFilePath = false;
    }

    std::cout << "set pat is :" << std::endl;
    for (list<string>::iterator i = var.begin(); i != var.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    logFile->setFilePath(var);
}

BaseConfigController LogController::queryBaseConfig() const
{
    return confData->baseConfig;
}

LogDataParam *LogController::getDataBufferObject() const
{
    return dataBuffer;
}

bool LogController::isSettingLogFilePath()
{
    return logFile->logPathVector() > 0;
}
