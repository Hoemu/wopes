#include "a_file_system.h"
#include <iostream>
#include "a_dir.h"

AFileSystem::AFileSystem(const string &targetPath) : filePath(targetPath)
{
    fileContents = "";
    dir = new ADir;
}

AFileSystem::~AFileSystem()
{
    if (dir != nullptr)
    {
        delete dir;
        dir = nullptr;
    }
}

void AFileSystem::setPath(const string &targetPath)
{
    this->filePath = targetPath;
}

bool AFileSystem::createFilePath(const string &var)
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

void AFileSystem::appendLine(const string &var)
{
    fwrite(var.c_str(), var.size(), 1, fp);
    fwrite(backEnter, strlen(backEnter), 1, fp);
}

void AFileSystem::clearContents()
{
    fileContents.clear();
}

bool AFileSystem::closeFile()
{
    return std::fclose(fp);
}

void AFileSystem::autoSaveFile(const int &fileMax)
{
    fseeko(fp, 0, SEEK_END);

    if (ftello(fp) % fileMax == fileMax)
    {
        closeFile();
        createFilePath("a");
    }
}

bool AFileSystem::isExist()
{
    return true;
}
