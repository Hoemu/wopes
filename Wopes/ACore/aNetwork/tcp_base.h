#ifndef TCP_BASE_H
#define TCP_BASE_H

#include <winsock.h>
#include "../ACore_global.h"

#pragma comment(lib, "ws2_32.lib")

class ACORE_EXPORT TCPBase
{
public:
    TCPBase();

    void setVersion(const u_int &var1, const u_int &var2);

    void initialization();

private:
    u_int ver1;
    u_int ver2;
};

#endif // TCP_BASE_H
