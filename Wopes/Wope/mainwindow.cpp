#include "mainwindow.h"
#include <iostream>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // a.print();
    ts = new ThreadTtest(this);
    std::cout << __FUNCTION__ << std::endl;
    acoreInit.getLogController()->setFilePath({ "./LogF/Warning_log" });
    acoreInit.getLogController()->setFoldFilePath(false);
    printQuery();
    LOG_INFO("input log.");
    LOG_ERROR("ERROR");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printQuery()
{
    BaseConfigController config = acoreInit.getLogController()->queryBaseConfig();
    std::cout << "[fold file path is ]:" << config.isfoldFilePath << ", ";
    std::cout << "[Console output is]:" << config.isConsoleOutput << ", ";
    std::cout << "[date log long use]:" << config.dateLogLongUse << ", ";
    std::cout << "[date log temp]:" << config.dateLogTemp << std::endl;
}

void MainWindow::on_btn_test_clicked()
{
    LOG_DEBUG("test");
}

void MainWindow::on_btn_begin_clicked()
{
    ts->begin();
}

void MainWindow::on_btn_end_clicked()
{
    ts->end();
}
