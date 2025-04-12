#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H
#include "../ACore_global.h"
#include "../aFileSystem/a_dir.h"
#include "log_file.h"

/** 日志控制器 */
class ACORE_EXPORT LogController
{
public:
    LogController();
    ~LogController();

    void setConfData(MsgData* var);

    void pushChar(MsgData* var);

    LogDataParam* getDataBufferObject() const;

    /** 设置日志配置 */
    void setConfig(LogConfig* configPtr);
    /** 设置日志配置 */
    void setConfig(shared_ptr<LogConfig> configPtr);
    /** 获取日志配置 */
    shared_ptr<LogConfig> getLogConfig() const;
    /** 载入日志配置（可直接进行修改） */
    shared_ptr<LogConfig> loadLogConfig();

    /** 日志文件设置 */
    void setFileSetting(LogFileSetting* feilSetting);
    /** 日志文件设置 */
    void setFilSetting(shared_ptr<LogFileSetting> feilSetting);
    /** 获取日志文件设置 */
    shared_ptr<LogFileSetting> getFileSetting() const;
    /** 载入日志文件设置（可直接进行修改） */
    shared_ptr<LogFileSetting> loadFileSetting();

    /** 启动日志（启动后配置最好不要做修改） */
    void start();

protected:
    void consoleLogPush(MsgData* var, const bool& isPush);

private:
    /** 一致性数据 */
    MsgData* confData;

    /** 日志配置指针（会设置初始内存） */
    shared_ptr<LogConfig> config;

    /** 日志文件设置指针（会设置初始内存） */
    shared_ptr<LogFileSetting> feilSetting;

    // 这个数据才是一段一段的
    LogFile* logFile;

    mutex configMutex;

    LogDataParam* dataBuffer;
};

#endif // LOGCONTROLLER_H
