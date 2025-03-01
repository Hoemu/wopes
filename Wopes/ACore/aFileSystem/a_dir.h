#ifndef A_DIR_H
#define A_DIR_H

#include <string>
#include "../ACore_global.h"
#ifdef _WIN32 // Includes both 32 bit and 64 bit
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using std::string;

class A_DECL_EXPORT ADir
{
public:
    ADir(const string &filePath = nullptr);

private:
    string mFilePath;
    string mFileDir;
};

#endif // A_DIR_H
