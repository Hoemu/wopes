#include "a_dir.h"
#include <iostream>
#include <vector>
#include "../aUtil/string_util.h"

ADir::ADir(const string &filePath) {}

ADir::~ADir() {}

bool ADir::makeDir(const string &filePath)
{
#ifdef _WIN32
    // Windows 模式 (支持正斜杠路径)
    return _mkdir(filePath.c_str()) == 0;
#else
    // Linux/Unix 模式 (需设置权限)
    return mkdir(path.c_str(), 0755) == 0;
#endif
}

bool ADir::createDir(const string &filePath)
{
    bool isDir = filePath[filePath.size() - 1] == '/';
    bool res = false;
    bool isPath = false;
    string noFilePathDir; // 没有文件的一个目录（去掉文件后的目录）

    if (isDir == true) // 为目录，会创建失败
    {
        return res;
    }

    mAcceptPath = filePath;
    mBuildPath = getExecutableDir();

    listSingleDir = StringUtil::split(filePath, "/");
    listBuildDir = StringUtil::split(mBuildPath, "\\/");
    mFileName = listSingleDir.back();

    if (mBuildPath.empty())
    {
        std::cerr << "m build path is empty." << std::endl;
        return res;
    }

    // 如果为相对路径，需要单独加上绝对路径，得到完整绝对路径
    if (listSingleDir.front() == "..")
    {
        int towPointCount = 0; // 两个点的计数
        for (const string &singleVar : listSingleDir)
        {
            if (singleVar != "..")
            {
                break;
            }
            else
            {
                listBuildDir.pop_back();
                towPointCount++;
            }
        }

        while (towPointCount--)
        {
            listSingleDir.pop_front();
        }
        mAcceptPath = StringUtil::combination(listSingleDir, "/");
    }
    else if (listSingleDir.front() == ".")
    {
        listSingleDir.pop_front();
        mAcceptPath = StringUtil::combination(listSingleDir, "/");
    }
    else // 此时必然是绝对路径
    {
        list<string> listPathAppend;
        listSingleDir.pop_back();
        for (const string &singleVar : listSingleDir)
        {
            listPathAppend.push_back(singleVar);

            if (listPathAppend.size() == 1)
            {
                continue;
            }

            noFilePathDir = StringUtil::combination(listPathAppend, "/", true);
            makeDir(noFilePathDir);
            mAcceptPath = noFilePathDir + mFileName;
        }
        res = isExitsPath(noFilePathDir);
        return res;
    }

    mAcceptPath = StringUtil::combination(listBuildDir, "/", true) + mAcceptPath; // 写入完整目录
    isPath = isExitsPath(mAcceptPath);                                            // 判断路径是否存在

    if (isPath == false)
    {
        listSingleDir = StringUtil::split(mAcceptPath, "/"); // 转化成目录 list（需要把文件先 pop 出去）
        list<string> listPathAppend;
        listSingleDir.pop_back();

        for (const string &singleVar : listSingleDir)
        {
            listPathAppend.push_back(singleVar);

            if (listPathAppend.size() == 1)
            {
                continue;
            }

            noFilePathDir = StringUtil::combination(listPathAppend, "/", true);
            makeDir(noFilePathDir);
            mAcceptPath = noFilePathDir + mFileName;
        }
    }

    res = isExitsPath(noFilePathDir);
    return res;
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
        // std::cerr << "[Warning]:Target path don't exists, parameter of function is : " << path << std::endl;
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
    if (!mAcceptPath.empty())
    {
        // std::cout << "[get file path]" << mAcceptPath << std::endl;
        return mAcceptPath;
    }
    std::cerr << "Geting file path is empty." << std::endl;
    return "";
}
