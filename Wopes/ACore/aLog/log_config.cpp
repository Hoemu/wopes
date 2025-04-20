#include "log_config.h"

#include <iostream>

LogConfig::LogConfig()
{
    configPtr = std::make_unique<BaseConfig>();
    configPtr->dateLogLongUse = true;
    configPtr->dateLogTemp = true;
    configPtr->consoleOutput = true;
    configPtr->foldFilePath = true;
    configPtr->logClassify = false;
    configPtr->existFilePath = false;
    configPtr->implement = false;
}

void LogConfig::setDataLogTemp(const bool &var)
{
    configPtr->dateLogTemp = var;
}

bool LogConfig::isDataLogTemp() const
{
    return configPtr->dateLogTemp;
}

void LogConfig::setDateLogLongUse(const bool &var)
{
    configPtr->dateLogLongUse = var;
}

void LogConfig::setConsoleOutput(const bool &var)
{
    configPtr->consoleOutput = var;
}

bool LogConfig::isConsoleOutput() const
{
    return configPtr->consoleOutput;
}

void LogConfig::setFoldFilePath(const bool &var)
{
    configPtr->foldFilePath = var;
}

bool LogConfig::isFoldFilePath() const
{
    return configPtr->foldFilePath;
}

void LogConfig::setLogClassify(const bool &var)
{
    configPtr->logClassify = var;
}

bool LogConfig::isLogClassify() const
{
    return configPtr->logClassify;
}

void LogConfig::setExistFilePath(const bool &var)
{
    configPtr->existFilePath = var;
}

bool LogConfig::isExistFilePath() const
{
    return configPtr->existFilePath;
}

void LogConfig::setImplement(const bool &var)
{
    configPtr->implement = var;
}

bool LogConfig::isImplement() const
{
    return configPtr->implement;
}

void LogConfig::printConfig()
{
    std::cout << "init log config:" << configPtr->dateLogLongUse << configPtr->dateLogTemp << configPtr->consoleOutput << configPtr->implement << std::endl;
}

bool LogConfig::isDataLogLongUse() const
{
    return configPtr->dateLogLongUse;
}

LogConfig::~LogConfig() {}
