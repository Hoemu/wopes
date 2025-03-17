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

    void setConsoleCondition(const bool& consoleCondition);

    /** 是否折叠输出的文件路径 */
    void setFoldFilePath(const bool& var);

    bool getIsFoldFilePath() const;

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

protected:
    void consoleLogPush(MsgData* var, const bool& isPush);

private:
    bool dateLogTemp;

    bool dateLogLongUse;

    ADir* dirTool;

    bool isConsoleOutput;

    bool isSettingLogFileCurrent;

    /** 是否折叠文件路径 */
    bool isfoldFilePath;

    // 这个数据才是一段一段的
    LogFile* logFile;

    LogDataParam* dataBuffer;
};

#endif // LOGCONTROLLER_H
