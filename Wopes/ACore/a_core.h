#ifndef A_CORE_H
#define A_CORE_H

#include <iostream>
#include "ACore_global.h"

using namespace std;

class ACORE_EXPORT ACore
{
public:
    ACore();

    void print();

    void test(){std::cout<<"test"<<std::endl;}
};

#endif // A_CORE_H
