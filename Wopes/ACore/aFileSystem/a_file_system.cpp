#include "a_file_system.h"
#include <iostream>
#include "a_dir.h"

AFileSystem::AFileSystem(const string &targetPath) : filePath(targetPath)
{
    maxContents = 0;
    fileContents = "";
    dir = new ADir;
}

AFileSystem::~AFileSystem()
{
    if (fp != NULL)
    {
        std::cout << "close file." << std::endl;
        std::fclose(fp);
    }

    if (dir != nullptr)
    {
        delete dir;
        dir = nullptr;
    }
}

inline void AFileSystem::setPath(const string &targetPath)
{
    this->filePath = targetPath;
}

inline bool AFileSystem::createFilePath(const string &var)
{
    // std::cout << "create file path:" << filePath << std::endl;

    dir->createDir(filePath);

    fp = fopen(dir->getFilePath().c_str(), var.c_str());

    if (fp == NULL)
    {
        // 打开失败，可能没有这个路径，那么就生成路径
        std::cerr << "Warning: file open fail:" << filePath << std::endl;
        return false;
    }

    return true;
}

inline void AFileSystem::appendLine(const string &var)
{
    // std::cout << "append:" << var << std::endl;
    fwrite(var.c_str(), var.size(), 1, fp);
    fwrite(backEnter, 1, 1, fp);
    // fflush(fp);
}

inline void AFileSystem::clearContents()
{
    fileContents.clear();
}

inline bool AFileSystem::closeFile()
{
    // std::cout << "close file." << std::endl;
    return std::fclose(fp);
}

inline bool AFileSystem::isExist()
{
    return true;
}
