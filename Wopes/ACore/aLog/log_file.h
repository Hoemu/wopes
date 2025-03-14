#ifndef LOGFILE_H
#define LOGFILE_H
#define unint unsigned int

#include <condition_variable>
#include <memory>
#include <mutex>
#include "../aFileSystem/a_file_system.h"
#include "log_data_param.h"

using std::iostream;

struct ThreadData
{
    //    void (LogFile::*callback)();
    unsigned int threadID = 0x0000;
    string filePath;
    std::shared_ptr<thread> threadPtr;
    bool isRunning;

    std::shared_ptr<LogDataParam> ptrDataParam;
};

struct ThreadCondition
{
    unsigned int threadID = 0x0000;
    std::mutex mMutex;
    std::condition_variable condConsumer;
};

class LogFile
{
public:
    // 注意这里面的数据是不生效的（并没有在当前线程下运行）
    LogFile();
    ~LogFile();

    /** 设置文件路径，只能初始化一次 */
    void setFilePath(list<string> var);

    void push(MsgData* data);

    void pushString(const string& data);

    int logPathVector() const;

protected:
    void runThread(const ThreadData& var);

    bool exitThread();

    /** 线程助手（一秒钟查看一次线程） */
    void threadHelperFunction();

    void wakeThread();

private:
    vector<ThreadData> vecThread;

    vector<ThreadCondition*> vecThreadCondition;

    queue<MsgData*> bufferData;

    std::shared_ptr<thread> threadHelper;
    bool isRunningThreadHelper;

    /** 文件路径个数 */
    int filePathNumber;
};

#endif // LOGFILE_H
