#include "tcp_base.h"
#include "../aUtil/acore_define.h"

TCPBase::TCPBase()
{
    // socket(AF_INET, SOCK_STREAM, 0);

    // WORD w_req = MAKEWORD(2, 2); // 版本号
    // WSADATA wsadata;
    // int err;
    // err = WSAStartup(w_req, &wsadata);
    // if (err != 0)
    // {
    //     cout << "初始化套接字库失败！" << endl;
    // }
    // else
    // {
    //     cout << "初始化套接字库成功！" << endl;
    // }
    // // 检测版本号
    // if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
    // {
    //     cout << "套接字库版本号不符！" << endl;
    //     WSACleanup();
    // }
    // else
    // {
    //     cout << "套接字库版本正确！" << endl;
    // }
}

void TCPBase::setVersion(const u_int &var1, const u_int &var2) {}
