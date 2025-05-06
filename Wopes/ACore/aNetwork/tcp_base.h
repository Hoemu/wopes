#ifndef TCP_BASE_H
#define TCP_BASE_H

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

class TCPBase
{
public:
    TCPBase();

    void initialization();
};

#endif // TCP_BASE_H
