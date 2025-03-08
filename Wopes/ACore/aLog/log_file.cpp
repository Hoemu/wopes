#include "log_file.h"
#include <iostream>
#include <thread>

LogFile::LogFile() {}

LogFile::~LogFile()
{
    if (!vecThread.empty())
    {
        while (vecThread[0].ptrDataParam->size())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        exitThread();
    }

    std::cout << "LogFile delete." << std::endl;
}

void LogFile::setFilePath(list<string> var)
{
    logFilePath = var;
    // TODO 重新设置需要结束线程
    exitThread();

    for (const string &path : logFilePath)
    {
        ThreadData data;
        ThreadCondition *condition = new ThreadCondition;
        data.ptrDataParam = std::make_unique<LogDataParam>();
        data.threadID = vecThread.size();
        data.isRunning = true;
        data.filePath = path;
        data.threadPtr = std::make_unique<thread>(&LogFile::runThread, this, data);
        vecThread.push_back(data);
        vecThreadCondition.push_back(condition);
    }
    // std::cout << "var size is:" << logFilePath.size() << std::endl;
}

void LogFile::push(const MsgData &data)
{
    if (vecThread.empty())
    {
        bufferData.push(data);
    }
    else if (!vecThread.empty() && !bufferData.empty())
    {
        while (!bufferData.empty())
        {
            for (ThreadData &fuc : vecThread)
            {
                fuc.ptrDataParam.get()->push(bufferData.front());
            }
            bufferData.pop();
        }
    }

    for (ThreadData &fuc : vecThread)
    {
        // std::cout << "push log input :" << data.msg << std::endl;
        fuc.ptrDataParam.get()->push(data);
        vecThreadCondition[fuc.threadID]->condConsumer.notify_one();
    }
}

void LogFile::pushString(const string &data)
{
    for (ThreadData &fuc : vecThread)
    {
        fuc.ptrDataParam.get()->pushString(data);
    }
}

int LogFile::logPathVector() const
{
    return vecThread.size();
}

void LogFile::runThread(const ThreadData &var)
{
    AFileSystem mFileSystem(var.filePath);
    mFileSystem.createFilePath("a");
    while (var.isRunning)
    {
        std::unique_lock<std::mutex> lock(vecThreadCondition[var.threadID]->mMutex);
        while (vecThread[var.threadID].ptrDataParam.get()->size() == 0)
        {
            mFileSystem.closeFile();
            mFileSystem.createFilePath("a");
            vecThreadCondition[var.threadID]->condConsumer.wait(lock); // 等待缓冲区不空
        }

        vecThread[var.threadID].dataFlag = true;
        string dataMsg = vecThread[var.threadID].ptrDataParam.get()->frontString();
        mFileSystem.appendLine(dataMsg);
        vecThread[var.threadID].ptrDataParam.get()->pop();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    mFileSystem.closeFile();
}

bool LogFile::exitThread()
{
    for (int i = 0; i < vecThread.size(); i++)
    {
        vecThread[i].isRunning = false;
        vecThread[i].threadPtr->detach();
        std::cout << "[clear]" << vecThread[i].filePath << std::endl;
    }
    vecThread.clear();
    return true;
}
