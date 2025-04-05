#ifndef TCP_H
#define TCP_H

class TCP
{
public:
    TCP();

    void connect();

    void open();

    bool isOpen();

    void close();
};

#endif // TCP_H
