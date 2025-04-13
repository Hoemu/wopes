#ifndef INTERNAL_SINGLETON_H
#define INTERNAL_SINGLETON_H

#include <atomic>
#include <mutex>

/** 懒汉模板 */
template<typename className>
class InternalSingleton
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
    InternalSingleton() {};
    virtual ~InternalSingleton() {};

private:
    InternalSingleton(const InternalSingleton&) = delete;
    InternalSingleton(const InternalSingleton&&) = delete;
    void operator=(const InternalSingleton&) = delete;
    static className* mInstance;
};
template<typename className>
className* InternalSingleton<className>::mInstance = nullptr; // 初始化为T类型的默认值

/** 懒汉模板（线程安全模式） */
template<typename lazyClass>
class SingletonLazy
{
public:
    static lazyClass* instance()
    {
        lazyClass* tmp = mInstance.load(std::memory_order_relaxed);
        if (tmp == nullptr)
        {
            std::lock_guard<std::mutex> lock(mtx); // 加锁
            tmp = mInstance.load(std::memory_order_relaxed);
            if (tmp == nullptr)
            {
                tmp = new lazyClass();
                mInstance.store(tmp, std::memory_order_release);
            }
        }
        return tmp;
    }

protected:
    SingletonLazy() {};
    virtual ~SingletonLazy() {};

private:
    static std::atomic<lazyClass*> mInstance; // 原子指针
    static std::mutex mtx;
    SingletonLazy(const SingletonLazy&) = delete;
    SingletonLazy& operator=(const SingletonLazy&) = delete;
};
template<typename lazyClass>
std::atomic<lazyClass*> SingletonLazy<lazyClass>::mInstance(nullptr);
template<typename lazyClass>
std::mutex SingletonLazy<lazyClass>::mtx;

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
