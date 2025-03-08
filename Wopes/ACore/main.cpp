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

TEST(ALOG, instace)
{
    acore::ACore aInit;
    aInit.getLogController()->setFilePath({ "../Log/Info_Log" });
    LOG_INFO("test");
    while (1) {}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
