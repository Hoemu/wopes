#include "a_core.h"

namespace acore
{
ACore::ACore()
{
    LOG_INFO("Init core."); // 测试用
    LOG_INFO("Init Log System.");
}

LogController *ACore::getLogController()
{
    return LogSystem::instance()->getControllerObject();
}

} // namespace acore
