#ifndef INTERNAL_SINGLETON_H
#define INTERNAL_SINGLETON_H

#include <atomic>
#include <mutex>

// 单例模板
// NOTE 写了三个模板，懒汉基础版，懒汉线程安全版，饿汉版

/** 懒汉模板 */
template<typename className>
class SingletonLazy
{
public:
    static className* instance()
    {
        if (mInstance == nullptr)
        {
            mInstance = new className;
        }
        return mInstance;
    };

    static void destroy()
    {
        if (mInstance != nullptr)
        {
            delete mInstance;
            mInstance = nullptr;
        }
    };

protected:
    SingletonLazy() {};
    virtual ~SingletonLazy() {};

private:
    SingletonLazy(const SingletonLazy&) = delete;
    SingletonLazy(const SingletonLazy&&) = delete;
    void operator=(const SingletonLazy&) = delete;
    static className* mInstance;
};
template<typename className>
className* SingletonLazy<className>::mInstance = nullptr; // 初始化为T类型的默认值

/** 懒汉模板（线程安全模式） */
template<typename lazySafeClass>
class SingletonLazySafe
{
public:
    static lazySafeClass* instance()
    {
        lazySafeClass* tmp = mInstance.load(std::memory_order_relaxed);
        if (tmp == nullptr)
        {
            std::lock_guard<std::mutex> lock(mtx); // 加锁
            tmp = mInstance.load(std::memory_order_relaxed);
            if (tmp == nullptr)
            {
                tmp = new lazySafeClass();
                mInstance.store(tmp, std::memory_order_release);
            }
        }
        return tmp;
    }

    static void destroy()
    {
        if (mInstance != nullptr)
        {
            delete mInstance;
            mInstance = nullptr;
        }
    };

protected:
    SingletonLazySafe() {};
    virtual ~SingletonLazySafe() {};

private:
    static std::atomic<lazySafeClass*> mInstance; // 原子指针
    static std::mutex mtx;
    SingletonLazySafe(const SingletonLazySafe&) = delete;
    SingletonLazySafe& operator=(const SingletonLazySafe&) = delete;
};
template<typename lazySafeClass>
std::atomic<lazySafeClass*> SingletonLazySafe<lazySafeClass>::mInstance(nullptr);
template<typename lazySafeClass>
std::mutex SingletonLazySafe<lazySafeClass>::mtx;

/** 饿汉模板（注：只能支持到毫秒级） */
template<typename eagerClass>
class SingletonEager
{
public:
    static eagerClass* instance()
    {
        std::lock_guard<std::mutex> lock(mtx); // 加锁
        return mInstance;                      // 直接返回已初始化的实例
    }

    static void destroy()
    {
        if (mInstance != nullptr)
        {
            delete mInstance;
            mInstance = nullptr;
        }
    };

protected:
    SingletonEager() {};
    virtual ~SingletonEager() {};

private:
    static eagerClass* mInstance; // 静态成员声明
    static std::mutex mtx;

    SingletonEager(const SingletonEager&) = delete;            // 禁止拷贝
    SingletonEager& operator=(const SingletonEager&) = delete; // 禁止赋值
};

// 类外初始化静态成员变量（程序启动时即创建）
template<typename eagerClass>
eagerClass* SingletonEager<eagerClass>::mInstance = new eagerClass();
template<typename eagerClass>
std::mutex SingletonEager<eagerClass>::mtx;

#endif // INTERNAL_SINGLETON_H
