#include <iostream>
#include "./aLog/log_define.h"
#include "./aUtil/string_util.h"
#include "aFileSystem/a_dir.h"

using std::cout;
using std::endl;

const string BEGING_STRING = "-------------------- insterface --------------------";
const string END_STRING = "-------------------- insterface END --------------------";
const string var = "C:/Users/Muiiii/Desktop/generalFile/GitRepertory/TEST/";
const string var2 = "./CUre/";

void interfaceTest(string var)
{
    std::cout << BEGING_STRING << std::endl;

    std::cout << "insterface test:" << _access(var.c_str(), 0) << std::endl;

    std::cout << END_STRING << std::endl;
}

int main()
{
    // LOG_INFO("main:");

    ADir initDir(var2);
    // // StringUtil::split(var, "/");
    initDir.printDir();
    // interfaceTest(var);
    std::cout << "dir is exist:" << initDir.isExitsPath("C:/cc") << std::endl;
    std::cout << "FileName is: " << initDir.getFileName() << "\nIs exist dir: " << initDir.currentDir() << std::endl;

    while (1) {} // 需要线程保持运行
    return 0;
}
