#ifndef A_DIR_H
#define A_DIR_H

#include <sys/stat.h>
#include <list>
#include <queue>
#include <string>
#include "../ACore_global.h"
#include "./a_abstract_dir.h"

#ifdef _WIN32
#include <direct.h> // Windows 专用头文件
#include <windows.h>
#else
#include <linux/limits.h>

#include <unistd.h>
#endif

using std::list;
using std::string;

/**
 * @brief 目录处理类，当前支持 '/' 目录（只对目录进行处理）
 */
class A_DECL_EXPORT ADir : public AAbstractDir
{
public:
    explicit ADir(const string &filePath);
    ~ADir();

    void cd();

    /**
     * @brief makeDir 创建目录
     * @param filePath
     * @return bool
     */
    bool makeDir(const string &filePath);

    void printDir();

    string currentDir() const;

    /**
     * @brief 是否存在目录
     * @return bool
     */
    bool isExistDir();

    string getFileName() const;

    bool isExitsPath(const string &path);

    string getExecutableDir();

    string getFilePath() const;

protected:
    /**
     *  @brief 判断路径是否存在
     */
    // constexpr bool isExitsPath() {};

    /**
     * @brief createDir 创建目录，为内部创建目录，更加完善判断
     * @param filePath
     * @return bool
     */
    bool createDir(const string &filePath);

private:
    /**
     * @brief 当前目录
     */
    string mFileDir;

    string mFileName;

    /**
     * @brief 构建路径（exe文件路径）
     */
    string mBuildPath;

    /**
     * @brief 类接收的文件路径
     */
    string mAcceptPath;

    bool isDir;
    bool isPath;

    list<string> listSingleDir;
    list<string> listBuildDir;
};

#endif // A_DIR_H
