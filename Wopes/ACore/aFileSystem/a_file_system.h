#ifndef A_FILE_SYSTEM_H
#define A_FILE_SYSTEM_H

#include <string>
#include "../ACore_global.h"

using std::string;

class A_DECL_EXPORT AFileSystem
{
public:
    AFileSystem(const string &targetPath = nullptr);

    void setPath(const string &targetPath);

    /**
     *  @brief 创建文件路径
     *  @param var 表示创建的文件规则
     */
    bool createFilePath(const string &var);

    void appendLine(const string &var);

    bool closeFile();

    /**
     * @brief 文件是否存在
     * @return bool
     */
    bool isExist();

private:
    string filePath;

    FILE *fp;
};

#endif // A_FILE_SYSTEM_H
