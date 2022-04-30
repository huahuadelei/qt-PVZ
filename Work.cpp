//
// Created by MIBOOK on 2022-04-24.
//

#include <iostream>
#include "Work.h"

HWND checkGameStarted();

Work::Work(QObject *parent):QThread(parent),executable(true){
}

void Work::run() {
    while (executable) {
        QThread::msleep(300);

        HWND hwnd = checkGameStarted();
//        std::cout<< flag << "----"<< hwnd << std::endl;
        if (hwnd != nullptr) {
            if(flag != 1){
                emit gameRuning(hwnd);
                flag = 1;
            }
        }else {

            if(flag != 0){
                emit gameNoRun();
                flag = 0;
            }
        }
    }
}

HWND checkGameStarted() {
    HWND hwnd = FindWindow((LPCWSTR)QString("MainWindow").unicode(), (LPCWSTR)QString("Plants vs. Zombies").unicode());
    return hwnd;
}

