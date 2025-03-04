#include "a_dir.h"
#include <iostream>
#include <vector>
#include "../aUtil/string_util.h"

ADir::ADir(const string &filePath)
{
    string targetString;

    isDir = filePath[filePath.size() - 1] == '/';
    mTargetPath = filePath;
    mBuildPath = getExecutableDir();

    listSingleDir = StringUtil::split(filePath, "/");
    listBuildDir = StringUtil::split(mBuildPath, "\\/");

    if (listSingleDir.front() == "..")
    {
        listSingleDir.pop_front();
        targetString = StringUtil::combination(listSingleDir, "/");
        listBuildDir.pop_back();
        // std::cout << "[ADir:]" << filePath << " stat: " << isPath << "\n exe path: " << mBuildPath << std::endl;
    }
    else if (listSingleDir.front() == ".")
    {
        listSingleDir.pop_front();
        targetString = StringUtil::combination(listSingleDir, "/");

        // std::cout << "[ADir:]" << filePath << " stat: " << isPath << "\n exe path: " << mBuildPath << std::endl;
    }

    // TODO 需要单独判断文件路径是否存在？
    isPath = isExitsPath(mTargetPath); // 判断路径是否存在
    mTargetPath = StringUtil::combination(listBuildDir, "/", !isDir) + targetString;

    createDir(mTargetPath);
}

ADir::~ADir() {}

void ADir::cd()
{
    std::cout << "cd.." << std::endl;
}

bool ADir::makeDir(const string &filePath)
{
    if (isDir == false)
    {
        return false;
    }
#ifdef _WIN32
    // Windows 模式 (支持正斜杠路径)
    return _mkdir(filePath.c_str()) == 0;
#else
    // Linux/Unix 模式 (需设置权限)
    return mkdir(path.c_str(), 0755) == 0;
#endif
}

void ADir::printDir()
{
    std::cout << "-------------------" << __FUNCTION__ << "-------------------" << std::endl;
    for (const string &var : listBuildDir)
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
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        std::cerr << "Target path don't exists, parameter of function is : " << path << std::endl;
        return false; // 路径不存在或不可访问
    }
    return (info.st_mode & S_IFDIR) != 0; // 检查是否为目录
}

string ADir::getExecutableDir()
{
    std::vector<char> buffer;
    size_t size = 1024;

    // 动态扩展缓冲区
    while (true)
    {
        buffer.resize(size);

#ifdef _WIN32
        DWORD result = GetModuleFileNameA(nullptr, &buffer.front(), size);
        if (result == 0)
        {
            return "";
        }
        if (result < size)
        {
            string path(buffer.begin(), buffer.begin() + result);
            size_t lastSlash = path.find_last_of("\\/");
            // std::cout << path << "------" << std::endl;
            path = (lastSlash != string::npos) ? path.substr(0, lastSlash) : path;
            return path;
        }
        size *= 2;
#else
        ssize_t result = readlink("/proc/self/exe", &buffer[0], size);
        if (result == -1)
            return "";
        if (static_cast<size_t>(result) < size)
        {
            std::string path(buffer.begin(), buffer.begin() + result);
            size_t lastSlash = path.find_last_of('/');
            return (lastSlash != std::string::npos) ? path.substr(0, lastSlash) : path;
        }
        size *= 2;
#endif
    }
}

string ADir::getFilePath() const
{
    if (!mTargetPath.empty())
    {
        std::cout << "[get file path]" << mTargetPath << std::endl;
        return mTargetPath;
    }
    std::cerr << "Geting file path is empty." << std::endl;
    return "";
}

bool ADir::createDir(const string &filePath)
{
    // 判断是否是目录
    if (isDir)
    {
        mFileName = "";
    }
    else
    {
        mFileName = listSingleDir.back();
        listSingleDir.pop_back();
        int index = filePath.find_last_of("/");
        mFileDir = filePath.substr(0, index + 1);
    }

    // 文件路径是否存在？
    if (isPath == false && isDir) // 注意：这里不会创建文件（只需要创建目录）
    {
        return makeDir(filePath);
    }
    else
    {
        std::clog << "[Warning]:Target path is filePath, don't switch to dir." << std::endl;
        return false;
    }
}
