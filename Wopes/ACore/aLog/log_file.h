#ifndef LOGFILE_H
#define LOGFILE_H
#define unint unsigned int

#include <map>

#include "log_data_param.h"
#include "log_file_setting.h"

using std::iostream;

class LogFile
{
public:
    // 注意这里面的数据是不生效的（并没有在当前线程下运行）
    LogFile();
    ~LogFile();

    void setFileSetting(shared_ptr<LogFileSetting> var);

    /** 启动文件线程 */
    void start();

    void pushChar(MsgData* data);

    int logPathVector() const;

protected:
    void runThread(const FileThreadData& var);

    bool exitThread();

private:
    vector<FileThreadData> vecThread;
    std::map<u_int, FileThreadData> threadMap;

    shared_ptr<LogFileSetting> fileSettingPtr;

    bool isRunningThreadHelper;

    /** 文件路径个数 */
    int filePathNumber;
};

#endif // LOGFILE_H
