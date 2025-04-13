#include "a_core.h"
#include <iostream>

namespace acore
{
ACore::ACore()
{
    LogSystem::instance();
}

ACore::~ACore() {}

LogController *ACore::getLogController()
{
    return LogSystem::instance()->getControllerObject();
}

shared_ptr<LogConfig> ACore::loadConfig()
{
    return LogSystem::instance()->getControllerObject()->loadLogConfig();
}

shared_ptr<LogFileSetting> ACore::loadFileSetting()
{
    return LogSystem::instance()->getControllerObject()->loadFileSetting();
}

} // namespace acore
