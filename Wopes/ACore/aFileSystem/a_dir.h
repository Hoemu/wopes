#ifndef A_DIR_H
#define A_DIR_H

#include <sys/stat.h>
#include <list>
#include <string>
#include "../ACore_global.h"

using std::list;
using std::string;

/**
 * @brief 目录处理类，当前支持 '/' 目录
 */
class A_DECL_EXPORT ADir
{
public:
    explicit ADir(const string &filePath);
    ~ADir();

    void cd();

    /**
     * @brief 创建文件夹
     * @return bool
     */
    bool mMkdir(const string &dir = nullptr);

    void printDir();

    string currentDir() const;

    /**
     * @brief 是否存在目录
     * @return bool
     */
    bool isExistDir();

    string getFileName() const;

    /**
     *  @brief 判断路径是否存在
     */
    static bool isExitsPath(const string &path);

protected:
    /**
     *  @brief 判断路径是否存在
     */
    // constexpr bool isExitsPath() {};

private:
    string mFilePath;
    string mFileDir;
    string mFileName;

    list<string> listSingleDir;
};

#endif // A_DIR_H
