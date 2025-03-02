#include "a_file_system.h"
#include <iostream>
#include "a_dir.h"

AFileSystem::AFileSystem(const string &targetPath) : filePath(targetPath) {}

void AFileSystem::setPath(const string &targetPath)
{
    this->filePath = targetPath;
}

bool AFileSystem::createFilePath(const string &var)
{
    if (ADir::isExitsPath(filePath) == false)
    {
        ADir adir(filePath);
        adir.mMkdir();
        // TODO 创建相关文件夹
    }

    fp = fopen(filePath.c_str(), var.c_str());

    if (fp == NULL)
    {
        // 打开失败，可能没有这个路径，那么就生成路径
        std::cerr << "Warning: file open fail:" << filePath << std::endl;
        return false;
    }
    return true;
}

void AFileSystem::appendLine(const string &var)
{
    string tempVar = var + "\n";
    fputs(tempVar.c_str(), fp);
}

bool AFileSystem::closeFile()
{
    return std::fclose(fp);
}

bool AFileSystem::isExist()
{
    return true;
}
