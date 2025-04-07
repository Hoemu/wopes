#include <gtest/gtest.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include "aLogTest.h"

const string var = "../TT/File/SS/GG";
const string var2 = "../../CUre/cc/FF";
const string DVar = "D:/Test/fff";

/** ****************************** 目录功能测试 */
TEST(ADir, DISABLED_isExistDir)
{
    ADir initDir;

    // initDir.createFilePath(var);
    initDir.makeDir(var);

    EXPECT_EQ(true, true);                         // 非致命断言（失败继续执行）
    ASSERT_NE(initDir.isExitsPath("./Dir"), true); // 致命断言（失败终止测试）
}

/** ****************************** psdlog 测试 */
TEST(spdlog, DISABLED_spdlog_test)
{
    const long long kLogCount = 100000000000;

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

/** ****************************** 多线程测试 */
TEST(LogThroughputTest, DISABLED_AtomicIncrement)
{
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG_1", "../Log/INFO_LOG_2" });
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
                // LOG_INFO("Test thread message: [" + std::to_string(i) + "] " + std::to_string(j));
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
/** ****************************** 单线程测试 */
TEST(LogThroughputTest, SingleThreadPerformance)
{
    const long long kLogCount = 10000;
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG_Char" });
    aLogInit.getLogController()->setConsoleCondition(false);
    auto start = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < kLogCount; ++i)
    {
        LOG_INFO(" Test log message: %d", i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();

    std::chrono::duration<double> result = end - start;

    double res = static_cast<double>(result.count());
    printf("OneThread costTime: %f,  %0.0f log/s\n", res, kLogCount / res);
    printf("OneThread costTime: %f,  %0.0f log/s\n", res, kLogCount / duration);
}

/** ****************************** 基础功能测试 */
TEST(LogThroughputTest, DISABLED_BaseTest)
{
    acore::ACore aLogInit;
    aLogInit.getLogController()->setFilePath({ "../Log/INFO_LOG_4" });
    aLogInit.getLogController()->setConsoleCondition(true);
    aLogInit.getLogController()->setFoldFilePath(true);
    std::cout << "DISABLED_BaseTest" << std::endl;
    // TEST_LOG("fdsaf");

    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG");
    LogSystem::instance()->setMessage("%s", "adf");
}

/** ****************************** 控制环境测试 */
TEST(LogController, DISABLED_setConsoleCondition)
{
    string a;
    // RingChunk ring(100);

    constexpr int kThreads = 2;
    constexpr int kIncrementsPerThread = 10000;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < kThreads; ++i)
    {
        threads.emplace_back([&]() {
            for (int j = 0; j < kIncrementsPerThread; ++j)
            {
                // ring.push("1234");
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
