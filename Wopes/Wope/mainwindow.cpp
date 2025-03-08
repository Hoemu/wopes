#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // a.print();
    acore::ACore acoreInit;
    acoreInit.getLogController()->setFilePath({ "./LogF/Warning_log" });

    LOG_INFO("输出日志");
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
