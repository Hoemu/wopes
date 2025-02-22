#include "a_core.h"
#include <iostream>

namespace ACore
{
ACore::ACore()
{
    LOG_INFO("Init core.");
}

void ACore::test()
{
    std::cout << "test" << std::endl;
}

void ACore::build()
{
    std::cout << "build running..." << std::endl;
}

} // namespace ACore
