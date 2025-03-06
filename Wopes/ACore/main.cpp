#include <iostream>
#include "./aLog/log_define.h"
#include "./aUtil/string_util.h"
#include "aFileSystem/a_dir.h"

#include <gtest/gtest.h>

using std::cout;
using std::endl;

void interfaceTest(string var);

const string BEGING_STRING = "-------------------- insterface --------------------";
const string END_STRING = "-------------------- insterface END --------------------";
const string var = "../TT/File/SS/GG";

const string var2 = "./CUre/cc";

TEST(ADir, isExistDir)
{
    // ADir initDir;

    // initDir.createFilePath(var);
    // initDir.makeDir(var);

    // EXPECT_EQ(initDir.isExistDir(), true); // 非致命断言（失败继续执行）
    // ASSERT_NE(initDir.isExistDir(), false); // 致命断言（失败终止测试）
}

int main(int argc, char** argv)
{
    // testing::InitGoogleTest(&argc, argv);
    LOG_INFO("main:");
    // return RUN_ALL_TESTS(); // google test

    // ADir initDir;
    // initDir.createFilePath(var);

    while (1) {} // 需要线程保持运行
    return 0;
}

void interfaceTest(string var)
{
    std::cout << BEGING_STRING << std::endl;
    std::cout << "insterface test:" << _access(var.c_str(), 0) << std::endl;
    std::cout << END_STRING << std::endl;
}
