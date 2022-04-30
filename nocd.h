#ifndef NOCD_H
#define NOCD_H

#include <QThread>
#include <QTimer>

class nocd: public QThread
{
    Q_OBJECT
public:
    explicit nocd(QObject *parent);
    ~nocd();
private:
    volatile bool isStart;
public:
    void start();
    void stop();
Q_SIGNALS:
    void timeout();


};

#endif // NOCD_H
