#include "log_file.h"
#include <iostream>
#include <thread>

LogFile::LogFile() {}

LogFile::~LogFile()
{
    std::cout << "LogFile delete." << std::endl;
}

void LogFile::setFilePath(list<string> var)
{
    logFilePath = var;

    for (const string &path : logFilePath)
    {
        functionData data;
        data.ptrDataParam = std::make_unique<LogDataParam>();
        data.threadID = vecThread.size();
        data.isRunning = true;
        data.filePath = path;
        data.th = new thread(&LogFile::runThread, this, data);
        vecThread.push_back(data);
    }
    // std::cout << "var size is:" << logFilePath.size() << std::endl;
}

void LogFile::push(const MsgData &data)
{
    for (functionData &fuc : vecThread)
    {
        fuc.ptrDataParam.get()->push(data);
    }
}

void LogFile::pushString(const string &data)
{
    for (functionData &fuc : vecThread)
    {
        fuc.ptrDataParam.get()->pushString(data);
    }
}

void LogFile::runThread(const functionData &var)
{
    AFileSystem mFileSystem(var.filePath);
    mFileSystem.createFilePath("a");

    while (var.isRunning)
    {
        // TODO 在没有日志时候保存文件，并关闭文件，当有日志的时候唤醒线程，并打开线程
        while (vecThread[var.threadID].ptrDataParam.get()->size())
        {
            vecThread[var.threadID].dataFlag = true;
            string dataMsg = vecThread[var.threadID].ptrDataParam.get()->frontString();
            // std::cout << "thread [" << var.threadID << "] " << dataMsg << std::endl;
            mFileSystem.appendLine(dataMsg);
            vecThread[var.threadID].ptrDataParam.get()->pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    mFileSystem.closeFile();
}
