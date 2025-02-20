#ifndef A_FILE_SYSTEM_H
#define A_FILE_SYSTEM_H

#include <filesystem>
#include <iostream>
#include <string>
#include "../ACore_global.h"

using std::string;
using namespace std::filesystem;

class A_DECL_EXPORT AFileSystem
{
public:
    AFileSystem(const string &targetPath);

    void setPath(const string &targetPath);

    void createFilePath();

    bool isExist();

private:
    string filePath;
};

#endif // A_FILE_SYSTEM_H
