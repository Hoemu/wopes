#include "log_controller.h"

LogController::LogController()
{
    dateLogLongUse = true;
    dateLogTemp = true;
    dataBuffer = new DataParam;
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

void LogController::push(const msg_data &var)
{
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

DataParam *LogController::getDataBufferObject() const
{
    return dataBuffer;
}
