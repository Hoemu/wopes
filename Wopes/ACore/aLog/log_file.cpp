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
        data.ptrDataParam = std::make_unique<DataParam>();
        data.threadID = vecThread.size();
        data.isRunning = true;
        data.filePath = path;
        data.th = new thread(&LogFile::run_thread, this, data);
        vecThread.push_back(data);
    }

    std::cout << "var size is:" << logFilePath.size() << std::endl;
}

void LogFile::push(const msg_data &data)
{
    for (functionData fuc : vecThread)
    {
        fuc.ptrDataParam.get()->push(data);
    }
}

void LogFile::run_thread(const functionData &var)
{
    string file_path = var.filePath;
    FILE *file = fopen(file_path.c_str(), "a");

    if (file == NULL)
    { // 打开失败直接返回
        std::cerr << "file open fail." << std::endl;
        return;
    }

    while (var.isRunning)
    {
        while (vecThread[var.threadID].ptrDataParam.get()->size())
        {
            vecThread[var.threadID].dataFlag = true;
            msg_data da = vecThread[var.threadID].ptrDataParam.get()->front();

            vector<string> logLevel = vecThread[var.threadID].ptrDataParam.get()->getLogLevel();
            string msgFile;
            //            std::cout << "thread [" << var.threadID << "] " << da.date << "." << da.ms << "=" << da.msg << std::endl;
            fputs(da.date, file); // 日期
            string msStr = "." + std::to_string(da.ms) + "] ";
            fputs(msStr.c_str(), file);                   // 毫秒
            fputs(logLevel[(int)da.model].c_str(), file); // 异常等级
            fputs(da.file.c_str(), file);                 // 文件
            string lineStr = " @" + std::to_string(da.line);
            fputs(lineStr.c_str(), file); // 文件长度
            string msgStr = " " + da.msg + "\n";
            fputs(msgStr.c_str(), file); // 文件长度
                                         //            fwrite(vecThread[var.threadID]ptrDataParam.get()->front().msg.c_str(), 0, 24, file); //写入操作
            vecThread[var.threadID].ptrDataParam.get()->pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    fclose(file);
}
