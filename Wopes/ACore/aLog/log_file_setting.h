#ifndef LOG_FILE_CONFIG_H
#define LOG_FILE_CONFIG_H

#include "../aFileSystem/a_file_system.h"
#include "log_config.h"
#include "log_data_param.h"

using std::make_shared;

struct FileThreadData
{
    //    void (LogFile::*callback)();
    unsigned int threadID = 0x0000;
    shared_ptr<thread> threadPtr;
    string filePath;
    bool isRunning;

    shared_ptr<LogDataParam> ptrDataParam;
    shared_ptr<AFileSystem> fileSystemPtr;
};

class ACORE_EXPORT LogFileSetting : public LogConfig
{
public:
    LogFileSetting();
    ~LogFileSetting();

    void setLogConfigPtr(shared_ptr<LogConfig> var);

    void setFilePathVector(const vector<string> &var);

    /** 获取目标文件路径，接收一个无符号整数索引 */
    string getTargetFilePath(const u_int at);

    /** 设置文件最大字节数 */
    void setFileMaxByte(const u_int &maxByte);
    /** 获取文件最大字节数 */
    u_int getFileMaxByte() const;

    u_int getLogFileNumber() const;

    shared_ptr<LogConfig> getLogConfig() const;

private:
    shared_ptr<FileThreadData> threadDataPtr;

    shared_ptr<LogConfig> config;

    vector<string> filePathList;

    u_int fileMaxByte;
};

#endif // LOG_FILE_CONFIG_H
