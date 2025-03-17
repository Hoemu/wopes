#ifndef THREADTTEST_H
#define THREADTTEST_H

#include <QThread>
#include "a_core.h"

class ThreadTtest : public QThread
{
    Q_OBJECT
public:
    ThreadTtest(QObject *parent = nullptr);

    void begin();

    void end();

protected:
    void run();

    void test();

private:
    bool isRunning;

    int i = 0;
};

#endif // THREADTTEST_H
