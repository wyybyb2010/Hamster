#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

enum GMode {BASEMODE, MIDMODE, HIGHMODE, CRAZYMODE};

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void  stopMyThread();
    void  changeMode(GMode mode);
protected:
    void run();
signals:
    void  myChangeIndex(int);
public slots:

private:
    int  stopFlags;
    GMode   m_mode;
    int     delayms;
};

#endif // MYTHREAD_H
