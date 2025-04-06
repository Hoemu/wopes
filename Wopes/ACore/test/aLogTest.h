#include <gtest/gtest.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include "../a_core.h"

using std::cout;
using std::endl;

class ACoreLog
{
public:
    ACoreLog();

    void test1();

    ~ACoreLog();

private:
};
