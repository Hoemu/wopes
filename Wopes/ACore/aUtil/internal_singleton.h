#ifndef INTERNAL_SINGLETON_H
#define INTERNAL_SINGLETON_H

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
    ~InternalSingleton() {};

    InternalSingleton(const InternalSingleton&) = delete;
    void operator=(const InternalSingleton&) = delete;

private:
    static className* mInstance;
};

template<typename className>
className* InternalSingleton<className>::mInstance = nullptr; // 初始化为T类型的默认值

#endif // INTERNAL_SINGLETON_H
