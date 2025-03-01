# aLog 模块文档
aLog 包含了多种日志输出方式，使用多线程管理，使用方式如下:

1. 首先导入 `ACore` 库
2. 代码书写模式如下:

```c++
#include <iostream>
#include "a_core.h"

int main()
{
    LOG_INFO("main:");
    return 0;
}
```

如果需要使用在类中，那么需要先声明并定义 `ACore` 这个类，如下所示：
```C++
#include "a_core.h"

class Test
{
    public:
        void Test(){
            acore::ACore acoreInit;
            LOG_INFO("输出日志");
        }
        void Test2(){
            LOG_ERROR("ERROR_LOG");
        }
}
```

3. 所支持类型

当前日志支持六种异常输出，如下所示
```C++
enum class LOG_LEVEL
{
    LOG_INFO = 0,
    LOG_DEBUG,
    LOG_DETUALT,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
};
```
