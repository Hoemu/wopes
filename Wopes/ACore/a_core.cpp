#include "a_core.h"
#include <iostream>
#include "aLog/log_define.h"
namespace ACore
{
ACore::ACore()
{
    initLog();
}

void ACore::print()
{
    LOG_INFO("init core.");
}

void ACore::test()
{
    std::cout << "test" << std::endl;
}

void ACore::build()
{
    std::cout << "build running..." << std::endl;
}

void ACore::initLog()
{
    LOG_INFO("Init Log")->setFilePath({ "./log/Error.log", "./log/log" });
}
} // namespace ACore
