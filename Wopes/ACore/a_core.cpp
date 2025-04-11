#include "a_core.h"
#include <iostream>

namespace acore
{
ACore::ACore()
{
    LogSystem::instance();
}

ACore::~ACore()
{
    LogSystem::destroy();
}

LogController *ACore::getLogController()
{
    return LogSystem::instance()->getControllerObject();
}

} // namespace acore
