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

    void push(const msg_data& var);

    /** 临时使用，需要手挡修改回去 */
    void useDateLogTemp(bool var);

    void operator>>(const std::string& var);

    void setFilePath(list<string> var);

    DataParam* getDataBufferObject() const;

private:
    bool dateLogTemp;

    bool dateLogLongUse;

    // 这个数据才是一段一段的
    DataParam* dataBuffer;

    LogFile* logFile;
};

#endif // LOGCONTROLLER_H
