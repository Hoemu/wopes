#include "log_file.h"
#include <iostream>
#include "../aFileSystem/a_file_system.h"

LogFile::LogFile()
{
    filePathNumber = 0;
    fileSettingPtr = make_shared<LogFileSetting>();
}

LogFile::~LogFile()
{
    // 确保日志完全写入文件
    quit();
    std::cout << "release logFile." << std::endl;
}

void LogFile::setFileSetting(shared_ptr<LogFileSetting> var)
{
    fileSettingPtr = var;
}

void LogFile::start()
{
    std::cout << "begin [start]" << std::endl;
    if (fileSettingPtr.use_count() == 0)
    {
        static_assert(true, "[ERROR]:File setting pointer is empty.");
        return;
    }

    for (int i = 0, n = fileSettingPtr->getLogFileNumber(); i < n; i++)
    {
        FileThreadData data;
        data.filePath = fileSettingPtr->getTargetFilePath(i);
        data.ptrDataParam = std::make_unique<LogDataParam>();
        data.threadID = n - 1;
        data.isRunning = true;
        data.threadPtr = std::make_shared<thread>(&LogFile::runThread, this, data);
        // data.threadPtr->detach();
        vecThread.push_back(data);
    }
}

void LogFile::quit()
{
    bool res = false;
    int threadSize = vecThread.size();
    for (int i = 0; i < threadSize; i++)
    {
        while (vecThread[i].ptrDataParam->sizeChar() != 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // vecThread[i].ptrDataParam->popChar();
        }

        vecThread[i].isRunning = res;
        vecThread[i].threadPtr->detach();
        vecThread[i].threadPtr.reset();
        std::cout << "[clear thread:] " << vecThread[i].filePath << std::endl;
    }
    vecThread.clear();
}

void LogFile::exit()
{
    int threadSize = vecThread.size();
    for (int i = 0; i < threadSize; i++)
    {
        vecThread[i].threadPtr.reset();
    }
    vecThread.clear();
}

void LogFile::pushChar(MsgData *data)
{
    for (FileThreadData &fuc : vecThread)
    {
        // std::cout << "push log input :" << data.msg << std::endl;
        fuc.ptrDataParam->pushChar(data);
    }
}

void LogFile::runThread(const FileThreadData &var)
{
    AFileSystem *mFileSystem = new AFileSystem(var.filePath);
    std::cout << "run thread is load success, var path is:" << var.filePath << std::endl;

    mFileSystem->createFilePath("a");
    while (var.isRunning)
    {
        while (var.isRunning && !vecThread[var.threadID].ptrDataParam->isEmpty())
        {
            mFileSystem->appendLine(vecThread[var.threadID].ptrDataParam->frontChar());
            vecThread[var.threadID].ptrDataParam->popChar();
        }
        // mFileSystem->closeFile();
        // mFileSystem->createFilePath("a");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    mFileSystem->closeFile();

    if (mFileSystem != nullptr)
    {
        delete mFileSystem;
        mFileSystem = nullptr;
    }
}
