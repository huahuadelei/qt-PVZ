//
// Created by MIBOOK on 2022-04-24.
//

#ifndef QT_CLION_WORK_H
#define QT_CLION_WORK_H

#include "windows.h"
#include <QThread>

class Work : public QThread {
Q_OBJECT

public:
    Work(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void gameRuning(HWND hwnd);
    void gameNoRun();

private:
    volatile bool executable = false;
    int flag=-1;
};

#endif //QT_CLION_WORK_H
