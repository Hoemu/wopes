#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

typedef unsigned int u_int;

using std::list;
using std::mutex;
using std::queue;
using std::shared_ptr;
using std::string;
using std::thread;
using std::unique_ptr;
using std::vector;

/** 基础配置 */
struct BaseConfig
{
    /** 日期日志临时使用 */
    bool dateLogTemp;

    /** 日期日志长期使用 */
    bool dateLogLongUse;

    /** 控制台输出 */
    bool consoleOutput;

    /** 是否折叠文件路径 */
    bool foldFilePath;

    /** 是否日志分类 */
    bool logClassify;

    /** 是否存在文件路径 */
    bool existFilePath;
};

/** 日志配置 */
class LogConfig
{
public:
    LogConfig();
    ~LogConfig();

    /** 设置是否短期日期日志 */
    void setDataLogTemp(const bool &var);
    /** 是否短期日期日志 */
    bool isDataLogTemp() const;

    /** 设置长期日期日志 */
    void setDateLogLongUse(const bool &var);
    /** 是否长期日期日志 */
    bool isDataLogLongUse() const;

    /** 设置控制台输出 */
    void setConsoleOutput(const bool &var);
    /** 是否控制台输出 */
    bool isConsoleOutput() const;

    /** 设置折叠文件路径 */
    void setFoldFilePath(const bool &var);
    /** 是否折叠文件路径 */
    bool isFoldFilePath() const;

    /** 设置日志分类 */
    void setLogClassify(const bool &var);
    /** 是否日志分类 */
    bool isLogClassify() const;

    /** 设置存在文件路径 */
    void setExistFilePath(const bool &var);
    /** 是否存在文件路径 */
    bool isExistFilePath() const;

private:
    unique_ptr<BaseConfig> configPtr;
};

#endif // LOG_CONFIG_H
