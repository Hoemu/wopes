#include "log_data_param.h"
#include <iostream>

LogDataParam::LogDataParam() {}

LogDataParam::~LogDataParam()
{
    while (!dataString.empty())
    {
        dataString.pop();
    }
}

const vector<string> &LogDataParam::getLogLevel() const
{
    return logLevel;
}

void LogDataParam::push(MsgData *var)
{
    mInputMutex.lock();
    string dataTemp = "[";
    dataTemp.insert(1, var->date);
    dataTemp = dataTemp + "." + std::to_string(var->ms % 1000) + "] ";
    dataTemp = dataTemp + logLevel[(int)var->model] + " ";
    dataTemp = dataTemp + var->file + ":(" + var->functionName + ")@";
    dataTemp = dataTemp + std::to_string(var->line) + " " + var->msg;

    dataString.emplace(dataTemp);
    // dataString.push(dataTemp);
    mInputMutex.unlock();
}

void LogDataParam::pop()
{
    mInputMutex.lock();
    if (dataString.empty())
    {
        std::cerr << "queue is empty." << std::endl;
        return;
    }

    dataString.pop();
    mInputMutex.unlock();
}

size_t LogDataParam::size()
{
    return dataString.size();
}

string LogDataParam::frontString() const
{
    return dataString.front();
}
