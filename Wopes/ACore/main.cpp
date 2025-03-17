#include <gtest/gtest.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
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

TEST(ADir, DISABLED_isExistDir)
{
    ADir initDir;

    // initDir.createFilePath(var);
    initDir.makeDir(var);

    EXPECT_EQ(true, true);                         // 非致命断言（失败继续执行）
    ASSERT_NE(initDir.isExitsPath("./Dir"), true); // 致命断言（失败终止测试）
}

TEST(spdlog, DISABLED_spdlog_test)
{
    const long long kLogCount = 10000000;

    auto file_logger = spdlog::basic_logger_mt("file_only", "../logs/app.log");

    // 替换默认日志器（可选）
    spdlog::set_default_logger(file_logger);

    auto start = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < kLogCount; ++i)
    {
        spdlog::info("Welcome to info spdlog!");
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();

    std::cout << "A thread throughput is: /n" << kLogCount / duration << " logs/sec\n";
}

TEST(LogThroughputTest, DISABLED_AtomicIncrement)
{
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG_TEST" });
    aLogInit.getLogController()->setConsoleCondition(false);

    constexpr int kThreads = 10;
    constexpr int kIncrementsPerThread = 10000;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < kThreads; ++i)
    {
        threads.emplace_back([=]() {
            for (int j = 0; j < kIncrementsPerThread; ++j)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                LOG_INFO("Test thread message: [" + std::to_string(i) + "] " + std::to_string(j));
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    // 输出性能指标
    std::cout << "File with buffer: " << duration.count() / (kThreads * kIncrementsPerThread) << " ns/op\n";

    // EXPECT_EQ(counter.GetCount(), kThreads * kIncrementsPerThread);
}

// DISABLED_  前缀：禁止测试项
TEST(LogThroughputTest, SingleThreadPerformance)
{
    const long long kLogCount = 10000000;
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG" });
    aLogInit.getLogController()->setConsoleCondition(false);
    auto start = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < kLogCount; ++i)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
        LOG_INFO("Test log message: " + std::to_string(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();

    std::cout << "A thread throughput is: /n " << kLogCount / duration << " logs/sec\n";
}

TEST(LogController, DISABLED_setConsoleCondition)
{
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG", "../Log/WARNING_LOG" });
    aLogInit.getLogController()->setFoldFilePath(true);
    LOG_INFO("Test log message: " + std::to_string(1));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
