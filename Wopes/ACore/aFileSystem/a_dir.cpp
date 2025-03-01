#include "a_dir.h"

ADir::ADir(const string &filePath) : mFilePath(filePath)
{
    size_t slash_pos = mFileDir.find_last_of('/'); // 查找最后一个斜杠
    mFileName = mFileDir.substr(slash_pos + 1);    // "image.jpg"

    for (size_t dirIndex = 0, preIndex = 0; dirIndex < filePath.size(); dirIndex++)
    {
        if (filePath[dirIndex] == '/')
        {
            string var = filePath.substr(preIndex, dirIndex);
            listSingleDir.push_back(var);
        }
    }
}

ADir::~ADir() {}


