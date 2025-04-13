#include "log_file.h"
#include <iostream>

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

    // std::cout << "get file number:" << fileSettingPtr->getLogFileNumber() << " " << fileSettingPtr->getTargetFilePath(0) << std::endl;
    for (int i = 0, n = fileSettingPtr->getLogFileNumber(); i < n; i++)
    {
        FileThreadData data;
        data.filePath = fileSettingPtr->getTargetFilePath(i);
        data.fileSystemPtr = std::make_shared<AFileSystem>(data.filePath);
        data.ptrDataParam = std::make_unique<LogDataParam>();
        data.threadID = n - 1;
        data.isRunning = true;
        data.threadPtr = std::make_shared<thread>(&LogFile::runThread, this, data);
        // data.threadPtr->detach();
        vecThread.push_back(data);
    }
    // std::cout << "{file number}:" << fileSettingPtr->getLogFileNumber() << ", {vecThread}:" << vecThread.size() << std::endl;
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

        vecThread[i].fileSystemPtr.reset();
        // std::cout << "[clear thread:] " << vecThread[i].filePath << " count:" << vecThread[i].fileSystemPtr.use_count() << std::endl;
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
    // std::cout << "push log input :" << data->msg << " vecThread:" << vecThread.size() << std::endl;
    for (FileThreadData &fuc : vecThread)
    {
        fuc.ptrDataParam->pushChar(data);
    }
}

void LogFile::runThread(const FileThreadData &var)
{
    shared_ptr<AFileSystem> mFileSystem = var.fileSystemPtr;

    std::cout << "run thread is load success, var path is:" << var.filePath << "var.isRunning:" << var.isRunning << std::endl;
    mFileSystem->createFilePath("a");

    while (var.isRunning)
    {
        bool res = vecThread[var.threadID].ptrDataParam->isEmpty();
        // std::cout << "var.threadID:" << var.threadID << std::endl;
        while (var.isRunning && !vecThread[var.threadID].ptrDataParam->isEmpty())
        {
            mFileSystem->appendLine(vecThread[var.threadID].ptrDataParam->frontChar());
            vecThread[var.threadID].ptrDataParam->popChar();
        }
        if (fileSettingPtr->getLogConfig()->isImplement())
        {
            mFileSystem->closeFile();
            mFileSystem->createFilePath("a");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
