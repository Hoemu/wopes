#include "a_core.h"
#include <iostream>

namespace acore
{
ACore::ACore() {}

ACore::~ACore()
{
    LogSystem::destroy();
}

LogController *ACore::getLogController()
{
    return LogSystem::instance()->getControllerObject();
}

} // namespace acore
