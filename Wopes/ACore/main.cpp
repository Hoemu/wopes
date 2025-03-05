#include <iostream>
#include "./aLog/log_define.h"
#include "./aUtil/string_util.h"
#include "aFileSystem/a_dir.h"

#include <gtest/gtest.h>
using std::cout;
using std::endl;

const string BEGING_STRING = "-------------------- insterface --------------------";
const string END_STRING = "-------------------- insterface END --------------------";
const string var = "C:/Users/Muiiii/Desktop/generalFile/GitRepertory/TEST/";
const string var2 = "./CUre/cc";

TEST(ExampleTest, BasicAssertions)
{
    EXPECT_EQ(1 + 1, 2); // 非致命断言（失败继续执行）
    ASSERT_NE(5, 0);     // 致命断言（失败终止测试）
}

void interfaceTest(string var)
{
    std::cout << BEGING_STRING << std::endl;

    std::cout << "insterface test:" << _access(var.c_str(), 0) << std::endl;

    std::cout << END_STRING << std::endl;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    LOG_INFO("main:");

    // ADir initDir(var2);
    // // StringUtil::split(var, "/");
    // initDir.printDir();
    // interfaceTest(var);
    // std::cout << "dir is exist:" << initDir.isExitsPath("C:/cc") << std::endl;
    // std::cout << "FileName is: " << initDir.getFileName() << "\nIs exist dir: " << initDir.currentDir() << std::endl;

    while (1) {} // 需要线程保持运行
    return 0;
}
