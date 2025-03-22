#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

#include <atomic>

class SpinLock
{
public:
    SpinLock() = default;
    SpinLock(const SpinLock &) = delete;
    SpinLock &operator=(const SpinLock &) = delete;

    void lock() noexcept
    {
        while (flag.test_and_set(std::memory_order_acquire))
        {
            // 针对不同CPU架构插入优化指令
#if defined(__x86_64__) || defined(__i386__)
            __builtin_ia32_pause(); // x86平台的pause指令
#elif defined(__arm__) || defined(__aarch64__)
            __asm__ __volatile__("yield"); // ARM平台的yield指令
#endif
        }
    }

    void unlock() noexcept
    {
        flag.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

template<typename SpinLock_>
class SpinLockGuard
{
public:
    typedef SpinLock_ mutex_type;

    SpinLockGuard(mutex_type &mDevice) : device_(mDevice)
    {
        device_.lock();
    };

    ~SpinLockGuard()
    {
        device_.unlock();
    };

    SpinLockGuard(const SpinLockGuard &) = delete;
    SpinLockGuard &operator=(const SpinLockGuard &) = delete;

private:
    mutex_type &device_;
};

#endif // SPIN_LOCK_H
