#include "mainwindow.h"

#include <QApplication>
#include <QThreadPool>
#include <qDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w->show();
    return a.exec();
}
