#include "a_file_system.h"
#include <iostream>

AFileSystem::AFileSystem(const string &targetPath) : filePath(targetPath) {}

void AFileSystem::setPath(const string &targetPath)
{
    this->filePath = targetPath;
}

bool AFileSystem::createFilePath(const string &var)
{
    fp = fopen(filePath.c_str(), var.c_str());

    if (fp == NULL)
    { // 打开失败直接返回
        std::cerr << "file open fail:" << filePath << std::endl;
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

bool AFileSystem::isExitsPath()
{

}
