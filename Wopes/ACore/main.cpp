#include <gtest/gtest.h>
#include <iostream>
#include "./aLog/log_define.h"
#include "./aUtil/string_util.h"
#include "aFileSystem/a_dir.h"
#include "a_core.h"

using std::cout;
using std::endl;

const string var = "../TT/File/SS/GG";
const string var2 = "../../CUre/cc/FF";
const string DVar = "D:/Test/fff";

TEST(ADir, isExistDir)
{
    ADir initDir;

    // initDir.createFilePath(var);
    initDir.makeDir(var);

    EXPECT_EQ(true, true);                         // 非致命断言（失败继续执行）
    ASSERT_NE(initDir.isExitsPath("./Dir"), true); // 致命断言（失败终止测试）
}

TEST(LogThroughputTest, SingleThreadPerformance)
{
    const int kLogCount = 100000;
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG", "../Log/WARNING_LOG" });
    aLogInit.getLogController()->setConsoleCondition(false);
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < kLogCount; ++i)
    {
        LOG_INFO("Test log message: " + std::to_string(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();

    std::cout << "A thread throughput is: /n" << kLogCount / duration << " logs/sec\n";
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
