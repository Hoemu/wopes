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

    /**
     *  @brief 创建文件路径
     *  @param var 表示创建的文件规则
     */
    bool createFilePath(const string &var);

    void appendLine(const string &var);

    void clearContents();

    bool closeFile();

    void autoSaveFile(const int &fileMax);

    /**
     * @brief 文件是否存在
     * @return bool
     */
    bool isExist();

private:
    string filePath;

    string fileContents;

    FILE *fp;

    ADir *dir;

    const char *backEnter = "\n";
};

#endif // A_FILE_SYSTEM_H
