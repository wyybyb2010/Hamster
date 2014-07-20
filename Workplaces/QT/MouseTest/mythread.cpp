#include "mythread.h"
#include <time.h>

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    qsrand(time(NULL));
    m_mode = BASEMODE;
    delayms = 1000 * 1000;
}
void MyThread::run()
{
    stopFlags = 1;
    int  curindex = 0;
    int  index = 0;
    while(stopFlags){
        index = qrand() % 9;
        if(index != curindex){
            emit  myChangeIndex(index);
            curindex = index;
        }
        usleep(delayms);
    }
}

void MyThread::changeMode(GMode mode)
{
    if(mode == m_mode) return;
    switch(mode){
    case BASEMODE:
        delayms = 1000 * 800;
        break;
    case MIDMODE:
        delayms = 1000 * 500;
        break;
    case HIGHMODE:
        delayms = 1000 * 300;
        break;
    case CRAZYMODE:
        delayms = 1000 * 150;
        break;
    default:break;
    }
}

void MyThread::stopMyThread()
{
    stopFlags = 0;
}
