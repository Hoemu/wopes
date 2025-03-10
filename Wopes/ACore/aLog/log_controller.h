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

    void useDateLog(bool var);

    bool getDateLog() const;

    bool getConsoleCondition() const;

    void setConsoleCondition(const bool& condition);

    /** 是否折叠输出的文件路径 */
    void setFoldFilePath(const bool& var);

    void push(MsgData* var);

    /** 临时使用，需要手挡修改回去 */
    void useDateLogTemp(bool var);

    void setFilePath(list<string> var);

    LogDataParam* getDataBufferObject() const;

    /**
     * @brief 是否设置日志目录
     * @return bool
     */
    bool isSettingLogFilePath();

private:
    bool dateLogTemp;

    bool dateLogLongUse;

    ADir* dirTool;

    /** 是否折叠文件路径 */
    bool isfoldFilePath;

    /** 控制台输出控制， true 为运行状态， false 为关闭状态 */
    bool consoleThread;

    // 这个数据才是一段一段的
    LogDataParam* dataBuffer;

    LogFile* logFile;
};

#endif // LOGCONTROLLER_H
