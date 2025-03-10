#include "mainwindow.h"
#include <iostream>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // a.print();
    std::cout << __FUNCTION__ << std::endl;
    acoreInit.getLogController()->setFilePath({ "./LogF/Warning_log" });
    acoreInit.getLogController()->setFoldFilePath(true);
    LOG_INFO("input log.");
    LOG_ERROR("ERROR");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_test_clicked()
{
    LOG_DEBUG("test");
}
