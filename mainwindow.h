#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "nocd.h"
#include "windows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    HANDLE hprocess = 0;
    QTimer *wuxiangSunnyTimer;
    QTimer *wulengqueTimer;

private slots:
    void setupComponentDisable();
    void setupComponentEnable(HWND hwnd);
    void findSunnyValueTask();

    void setSunnyOf(int value);
    void resetCooling();

    void on_pushButton_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
};
#endif // MAINWINDOW_H
