#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include "../ACore/a_core.h"
// #include <ACore>
#include "a_core.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_test_clicked();

private:
    Ui::MainWindow *ui;

    acore::ACore acoreInit;
};
#endif // MAINWINDOW_H
