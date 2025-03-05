#ifndef A_ABSTRACT_DIR_H
#define A_ABSTRACT_DIR_H

/**
 * @brief The AAbstractDir class 目录抽象类，只提供数据和接口，不提供实现
 */
class AAbstractDir
{
public:
    enum ADirParam
    {
        /** 相对路径 */
        RelativePaths,
        /** 绝对路径 */
        AbsolutePaths
    };

    AAbstractDir();
};

#endif // A_ABSTRACT_DIR_H
