#ifndef A_FILE_SYSTEM_H
#define A_FILE_SYSTEM_H

#include <string>
#include "../ACore_global.h"
#include "a_dir.h"

using std::string;

class A_DECL_EXPORT AFileSystem
{
public:
    AFileSystem(const string &targetPath = nullptr);
    ~AFileSystem();

    void setPath(const string &targetPath);

    /** 创建文件路径 */
    bool createFilePath(const string &var);

    void appendLine(const string &var);

    void clearContents();

    bool closeFile();

    /** 文件是否存在 */
    bool isExist();

private:
    string filePath;

    string fileContents;

    unsigned int chCount;

    unsigned int maxContents;

    FILE *fp;

    ADir *dir;

    const char *backEnter = "\n";
};

#endif // A_FILE_SYSTEM_H
