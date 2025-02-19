#include "a_core.h"
#include "aLog/log_define.h"
#include <iostream>
namespace ACore {
ACore::ACore() {}

void ACore::print() {
  std::cout << "print_F" << std::endl;
  LOG_INFO("init core.");
}

void ACore::test() { std::cout << "test" << std::endl; }

void ACore::build() { std::cout << "build running..." << std::endl; }
} // namespace ACore
