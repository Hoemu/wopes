#ifndef LOGFILE_H
#define LOGFILE_H
#define unint unsigned int

#include <memory>
#include "../aFileSystem/a_file_system.h"
#include "log_data_param.h"

using std::iostream;

struct functionData
{
    //    void (LogFile::*callback)();
    unsigned int threadID = 0x0000;
    string filePath;
    thread* th;
    bool isRunning;
    bool dataFlag = false;
    std::shared_ptr<LogDataParam> ptrDataParam;
};

class LogFile
{
public:
    // 注意这里面的数据是不生效的（并没有在当前线程下运行）
    LogFile();
    ~LogFile();

    /** 设置文件路径，只能初始化一次 */
    void setFilePath(list<string> var);

    void push(const MsgData& data);

    void pushString(const string& data);

    int logPathVector() const;

protected:
    void runThread(const functionData& var);

    bool exitThread();

private:
    /** 日志路径 */
    list<string> logFilePath;

    vector<functionData> vecThread;

    queue<MsgData> bufferData;
};

#endif // LOGFILE_H
