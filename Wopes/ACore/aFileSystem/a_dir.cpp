#include "a_dir.h"
#include <iostream>
#include "../aUtil/string_util.h"

ADir::ADir(const string &filePath) : mFilePath(filePath)
{
    int preIndex = 0;
    int len = 0;
    bool isDir = !isExitsPath(filePath);

    listSingleDir = StringUtil::split(filePath, "/");
    std::cout << "ADir:" << filePath << std::endl;

    if (isDir != true)
    {
        mFileName = listSingleDir.back();
        listSingleDir.pop_back();
        int index = filePath.find_last_of("/");
        mFileDir = filePath.substr(0, filePath.size() - index);
        std::cout << "mFileDir:" << mFileDir << std::endl;
    }
    else
    {
        mFileDir = filePath;
    }
}

ADir::~ADir() {}

void ADir::cd()
{
    std::cout << "cd.." << std::endl;
}

bool ADir::mMkdir(const string &dir)
{
    // TODO 注意这里区分 windows 环境和 linux 环境
    bool res = false;
    if (dir.empty())
    {
        res = mkdir(mFileDir.c_str()) == 0;
    }
    else
    {
        res = mkdir(dir.c_str()) == 0;
    }
    return res;
}

void ADir::printDir()
{
    std::cout << "-------------------" << __FUNCTION__ << "-------------------" << std::endl;
    for (const string &var : listSingleDir)
    {
        std::cout << var << "\n";
    }
    std::cout << "\n";
    std::cout << "-------------------"
              << "END"
              << "-------------------" << std::endl;
}

string ADir::currentDir() const
{
    return mFileDir;
}

bool ADir::isExistDir()
{
    return _access(mFileDir.c_str(), 0) == 0;
}

string ADir::getFileName() const
{
    return mFileName;
}

bool ADir::isExitsPath(const string &path)
{
    FILE *tFp = fopen(path.c_str(), "r");
    if (tFp == NULL)
    {
        return false;
    }
    fclose(tFp);
    return true;
}
