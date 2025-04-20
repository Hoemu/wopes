#include "log_controller.h"
#include <iostream>

LogController::LogController()
{
    config = std::make_shared<LogConfig>();
    feilSetting = std::make_shared<LogFileSetting>();
    feilSetting->setLogConfigPtr(config);

    dataBuffer = new LogDataParam;
    logFile = new LogFile;

    logFile->setFileSetting(feilSetting);

    feilSetting->printConfig();
}

LogController::~LogController()
{
    delete logFile;
    delete dataBuffer;
}

void LogController::setConfData(MsgData *var)
{
    std::cout << "set conf data is success." << std::endl;
    confData = var;
}

void LogController::pushChar(MsgData *var)
{
    if (!config->isExistFilePath())
    {
        static_assert(true, "[ERROR]:Don't set log path");
        // std::cerr << "[ERROR]:Don't set log path: " << var->msg << std::endl;
    }

    consoleLogPush(var, config->isConsoleOutput());
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

LogDataParam *LogController::getDataBufferObject() const
{
    return dataBuffer;
}

void LogController::setConfig(LogConfig *configPtr)
{
    std::lock_guard<mutex> guard(configMutex);
    config.reset(configPtr);
}

void LogController::setConfig(shared_ptr<LogConfig> configPtr)
{
    std::lock_guard<mutex> guard(configMutex);
    config = configPtr;
}

shared_ptr<LogConfig> LogController::getLogConfig() const
{
    return config;
}

shared_ptr<LogConfig> LogController::loadLogConfig()
{
    return config;
}

shared_ptr<LogFileSetting> LogController::getFileSetting() const
{
    return feilSetting;
}

shared_ptr<LogFileSetting> LogController::loadFileSetting()
{
    return feilSetting;
}

void LogController::start()
{
    logFile->start();
}
