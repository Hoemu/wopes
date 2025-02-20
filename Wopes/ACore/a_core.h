#ifndef A_CORE_H
#define A_CORE_H

#include "ACore_global.h"

namespace ACore
{
class ACORE_EXPORT ACore
{
public:
    ACore();

    void print();

    void test();

    void build();

private:
    void initLog();
};
} // namespace ACore

#endif // A_CORE_H
