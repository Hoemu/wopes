#include "log_file_setting.h"
#include <iostream>

LogFileSetting::LogFileSetting()
{
    threadDataPtr = make_shared<FileThreadData>();
    // threadDataPtr->threadPtr = shared_ptr<thread>();
    threadDataPtr->ptrDataParam = make_shared<LogDataParam>();
    fileMaxByte = 0;
    filePathList = {};
}

LogFileSetting::~LogFileSetting() {}

void LogFileSetting::setLogConfigPtr(shared_ptr<LogConfig> var)
{
    config = var;
}

void LogFileSetting::setFilePathVector(const vector<string> &var)
{
    if (var.empty())
    {
        config->setExistFilePath(false);
        std::cerr << "file path is empty." << std::endl;
    }
    else
    {
        config->setExistFilePath(true);
    }

    filePathList = var;
}

string LogFileSetting::getTargetFilePath(const u_int at)
{
    return filePathList[at];
}

void LogFileSetting::setFileMaxByte(const u_int &maxByte)
{
    fileMaxByte = maxByte;
}

u_int LogFileSetting::getFileMaxByte() const
{
    return fileMaxByte;
}

u_int LogFileSetting::getLogFileNumber() const
{
    if (filePathList.empty())
    {
        std::cerr << "file path number is empty." << std::endl;
    }

    return filePathList.size();
}
