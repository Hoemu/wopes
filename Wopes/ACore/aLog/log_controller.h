#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include "../ACore_global.h"
#include "log_file.h"

/** 日志控制器 */
class ACORE_EXPORT LogController
{
public:
    LogController();
    ~LogController();

    void useDateLog(bool var);

    bool getDateLog() const;

    void push(const MsgData& var);

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

    // 这个数据才是一段一段的
    LogDataParam* dataBuffer;

    LogFile* logFile;
};

#endif // LOGCONTROLLER_H
