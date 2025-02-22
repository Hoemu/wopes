#include "log_data_param.h"

queue<MsgData> &LogDataParam::getDataBuffer()
{
    return data;
}

const vector<string> &LogDataParam::getLogLevel() const
{
    return logLevel;
}

void LogDataParam::push(const MsgData &var)
{
    string dataTemp = "[";
    dataTemp.insert(1, var.date);
    dataTemp = dataTemp + "." + std::to_string(var.ms % 1000) + "] ";
    dataTemp = dataTemp + logLevel[(int)var.model] + " ";
    dataTemp = dataTemp + var.file + ":(" + var.functionName + ")@";
    dataTemp = dataTemp + std::to_string(var.line) + " " + var.msg;
    dataString.push(dataTemp);
    data.push(var);
}

void LogDataParam::pushString(const string &str)
{
    dataString.push(str);
    // TODO 以字符串的形式 push 也需要解析
}

void LogDataParam::pop()
{
    dataString.pop();
    data.pop();
}

size_t LogDataParam::size()
{
    return data.size();
}

MsgData LogDataParam::front() const
{
    return data.front();
}

string LogDataParam::frontString() const
{
    return dataString.front();
}
