#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H
#include "../ACore_global.h"
#include "../aFileSystem/a_dir.h"
#include "log_file.h"

struct BaseConfigController
{
    bool dateLogTemp;

    bool dateLogLongUse;

    bool isConsoleOutput;

    bool isSettingLogFileCurrent;

    /** 是否折叠文件路径 */
    bool isfoldFilePath;

    /** 是否日志分类 */
    bool isLogClassify;
};

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

    void setFileMaxByte(unsigned int max);

    void pushChar(MsgData* var);

    /** 临时使用，需要手挡修改回去 */
    void useDateLogTemp(bool var);

    void setFilePath(list<string> var);

    /** 查询基本配置 */
    BaseConfigController queryBaseConfig();

    LogDataParam* getDataBufferObject() const;

    /**
     * @brief 是否设置日志目录
     * @return bool
     */
    bool isSettingLogFilePath();

protected:
    void consoleLogPush(MsgData* var, const bool& isPush);

private:
    ADir* dirTool;

    BaseConfigController config;

    // 这个数据才是一段一段的
    LogFile* logFile;

    LogDataParam* dataBuffer;
};

#endif // LOGCONTROLLER_H
