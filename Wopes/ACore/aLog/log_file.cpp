#include "log_file.h"
#include <thread>

LogFile::LogFile() {}

LogFile::~LogFile() {}

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
        data.th = new thread(&LogFile::run_thread, this, data);
        vecThread.push_back(data);
    }

    // std::cout << "var size is:" << logFilePath.size() << std::endl;
}

void LogFile::push(const MsgData &data)
{
    for (functionData fuc : vecThread)
    {
        fuc.ptrDataParam.get()->push(data);
    }
}

void LogFile::pushString(const string &data)
{
    for (functionData fuc : vecThread)
    {
        fuc.ptrDataParam.get()->pushString(data);
    }
}

void LogFile::run_thread(const functionData &var)
{
    string file_path = var.filePath;
    FILE *file = fopen(file_path.c_str(), "a");

    if (file == NULL)
    { // 打开失败直接返回
        std::cerr << "file open fail:" << file_path << std::endl;
        return;
    }

    while (var.isRunning)
    {
        while (vecThread[var.threadID].ptrDataParam.get()->size())
        {
            vecThread[var.threadID].dataFlag = true;
            string dataMsg = vecThread[var.threadID].ptrDataParam.get()->frontString();
            //            std::cout << "thread [" << var.threadID << "] " << da.date << "." << da.ms << "=" << da.msg << std::endl;
            fputs(dataMsg.c_str(), file);
            fputs("\n", file); // 文件长度
            vecThread[var.threadID].ptrDataParam.get()->pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    fclose(file);
}
