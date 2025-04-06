#include "a_core.h"
#include <iostream>

namespace acore
{
ACore::ACore()
{
    LogSystem::instance();
    // TEST_LOG("init acore.");
}

ACore::~ACore()
{
    LogSystem::destroy();
}

LogController *ACore::getLogController()
{
    std::cout << "get log controller." << std::endl;
    return LogSystem::instance()->getControllerObject();
}

} // namespace acore
