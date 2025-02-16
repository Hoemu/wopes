#include "data_param.h"

queue<msg_data> &DataParam::getDataBuffer()
{
    return data;
}

const vector<string> &DataParam::getLogLevel() const
{
    return logLevel;
}

void DataParam::push(const msg_data &var)
{
    data.push(var);
}

void DataParam::pop()
{
    data.pop();
}

size_t DataParam::size()
{
    return data.size();
}

msg_data DataParam::front() const
{
    return data.front();
}
