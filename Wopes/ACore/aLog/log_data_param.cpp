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

void LogDataParam::pushString(const string &str)
{
    dataString.push(str);
    for (int i = 0; i < str.size(); i++) {}
    // TODO 以字符串的形式 push 也需要解析
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
    size_t si = dataString.size();
    return si;
}

string LogDataParam::frontString() const
{
    return dataString.front();
}
