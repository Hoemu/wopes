#ifndef A_DIR_H
#define A_DIR_H

#include <sys/stat.h>
#include <list>
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
    explicit ADir(const string &filePath = "");
    ~ADir();

    /**
     * @brief makeDir 创建目录
     * @param filePath
     * @return bool
     */
    bool makeDir(const string &filePath);

    /**
     * @brief createDir 创建一个目录（需要自带文件名称才能创建成功，注意：如果文件路径已经存在了，也可能创建失败）
     * @param filePath
     * @return bool
     */
    bool createDir(const string &filePath);

    string getFileName() const;

    bool isExitsPath(const string &path);

    string getExecutableDir();

    string getFilePath() const;

private:
    string mFileName;

    /**
     * @brief 构建路径（exe文件路径）
     */
    string mBuildPath;

    /**
     * @brief 类接收的文件路径
     */
    string mAcceptPath;

    list<string> listSingleDir;
    list<string> listBuildDir;
};

#endif // A_DIR_H
