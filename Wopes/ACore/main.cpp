#include <gtest/gtest.h>
#include <iostream>
#include "./aLog/log_define.h"
#include "./aUtil/string_util.h"
#include "aFileSystem/a_dir.h"

using std::cout;
using std::endl;

const string BEGING_STRING = "-------------------- insterface --------------------";
const string END_STRING = "-------------------- insterface END --------------------";
const string var = "../TT/File/SS/GG";

const string var2 = "./CUre/cc";
const string DVar = "D:/Test/fff";

TEST(ADir, isExistDir)
{
    ADir initDir;

    // initDir.createFilePath(var);
    initDir.makeDir(var);

    EXPECT_EQ(initDir.createDir(DVar), true);      // 非致命断言（失败继续执行）
    ASSERT_NE(initDir.isExitsPath("./Dir"), true); // 致命断言（失败终止测试）
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    LOG_INFO("main:");
    return RUN_ALL_TESTS(); // google test
}
