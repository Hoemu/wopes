#include "log_file.h"
#include <iostream>

LogFile::LogFile()
{
    filePathNumber = 0;
}

LogFile::~LogFile()
{
    // 确保日志完全写入文件
    exitThread();
    std::cout << "LogFile delete." << std::endl;
}

void LogFile::setFilePath(list<string> var)
{
    filePathNumber = var.size();
    exitThread();

    for (const string &path : var)
    {
        ThreadData data;
        data.ptrDataParam = std::make_unique<LogDataParam>();
        data.threadID = vecThread.size();
        data.isRunning = true;
        data.filePath = path;
        data.threadPtr = std::make_unique<thread>(&LogFile::runThread, this, data);
        vecThread.push_back(data);
    }
    // std::cout << "var size is:" << logFilePath.size() << std::endl;
}

void LogFile::pushChar(MsgData *data)
{
    for (ThreadData &fuc : vecThread)
    {
        // std::cout << "push log input :" << data.msg << std::endl;
        fuc.ptrDataParam->pushChar(data);
    }
}

int LogFile::logPathVector() const
{
    return vecThread.size();
}

void LogFile::runThread(const ThreadData &var)
{
    AFileSystem *mFileSystem = new AFileSystem(var.filePath);

    mFileSystem->createFilePath("a");
    while (var.isRunning)
    {
        while (vecThread[var.threadID].ptrDataParam->sizeChar() != 0)
        {
            mFileSystem->appendLine(vecThread[var.threadID].ptrDataParam.get()->frontChar());
            vecThread[var.threadID].ptrDataParam.get()->popChar();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    mFileSystem->closeFile();

    if (mFileSystem != nullptr)
    {
        delete mFileSystem;
        mFileSystem = nullptr;
    }
}

bool LogFile::exitThread()
{
    for (int i = 0; i < vecThread.size(); i++)
    {
        while (vecThread[i].ptrDataParam->sizeChar() != 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        vecThread[i].isRunning = false;
        vecThread[i].threadPtr->detach();
        std::cout << "[clear] " << vecThread[i].filePath << std::endl;
    }
    vecThread.clear();
    return true;
}
