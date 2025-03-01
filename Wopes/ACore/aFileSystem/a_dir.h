#ifndef A_DIR_H
#define A_DIR_H

#include <sys/stat.h>
#include <list>
#include <string>
#include "../ACore_global.h"

using std::list;
using std::string;

class A_DECL_EXPORT ADir
{
public:
    ADir(const string& filePath = nullptr);
    ~ADir();

    void cd();

    bool mMkdir();

private:
    string mFilePath;
    string mFileDir;
    string mFileName;

    list<string> listSingleDir;
};

#endif // A_DIR_H
