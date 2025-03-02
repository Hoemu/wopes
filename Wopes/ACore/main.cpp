#include <iostream>
#include "./aLog/log_define.h"
#include "./aUtil/string_util.h"
#include "aFileSystem/a_dir.h"

const string BEGING_STRING = "-------------------- insterface --------------------";
const string END_STRING = "-------------------- insterface END --------------------";

void interfaceTest(string var)
{
    std::cout << BEGING_STRING << std::endl;

    std::cout << "insterface test:" << _access(var.c_str(), 0) << std::endl;

    std::cout << END_STRING << std::endl;
}

int main()
{
    LOG_INFO("main:");
    std::cout << "hello world--" << std::endl;
    string var = "C:/Users/Muiiii/Desktop/generalFile/GitRepertory/test.cpp";
    string var2 = "./CUre";
    ADir initDir(var);
    // StringUtil::split(var, "/");
    initDir.printDir();
    interfaceTest(var);
    std::cout << initDir.getFileName() << "\nIs exist dir:" << initDir.currentDir() << std::endl;
    initDir.cd();
    while (1) {} // 需要线程保持运行
    return 0;
}
