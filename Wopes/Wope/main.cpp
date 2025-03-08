#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int print(const char *__format, ...)
{
    int retval;
    __builtin_va_list __local_argv;
    __builtin_va_start(__local_argv, __format);
    retval = __mingw_vfprintf(stdout, __format, __local_argv);
    __builtin_va_end(__local_argv);
    return retval;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    printf("\ntset %1", 12);
    w.show();
    std::cout << "asdf";
    return a.exec();
}
