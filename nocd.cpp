#include "nocd.h"
#include "QObject"
#include "qdebug.h"

nocd::nocd(QObject *parent):QObject(parent)
{
    thread = new QThread();
    timer = new QTimer;
    timer->setInterval(std::chrono::milliseconds(200));
    timer->setSingleShot(true);
    timer->moveToThread(thread);

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
}
nocd::~nocd(){
    delete thread;
    delete timer;
}
void nocd::handleTimeout(){
    qDebug() << "111";
}

void nocd::start(){
    thread->start();

}

void nocd::stop(){
    timer->stop();
}
