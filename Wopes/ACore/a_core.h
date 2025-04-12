#ifndef A_CORE_H
#define A_CORE_H

#include "ACore_global.h"
#include "aLog/log_define.h"

namespace acore
{
class ACORE_EXPORT ACore
{
public:
    ACore();
    ~ACore();

    /**
     * @brief 获取日志控制器
     */
    LogController *getLogController();

    shared_ptr<LogConfig> loadConfig();

    shared_ptr<LogFileSetting> loadFileSetting();

private:
};
} // namespace acore

#endif // A_CORE_H
