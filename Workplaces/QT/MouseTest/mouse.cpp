#include "mouse.h"
#include <QMouseEvent>
#include <QDebug>

Mouse::Mouse(QWidget *parent) :
    QAbstractButton(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(flyUpImage()));
    yPos = this->height();
    rate = 50;
    upflags = 0;
}

void Mouse::flyUpImage()
{
    if(yPos <= 0){
        upflags = 1;
    }else if(yPos >= this->height()){
        upflags = 0;
    }

    if(!upflags){
        yPos -= 5;
    }else{
        yPos += 5;
    }

    update();
}

void Mouse::mousePressEvent(QMouseEvent *e)
{
    click();
    e->ignore();
}


void Mouse::setBackImage(QString filepath, int lvl)
{
    img.load(filepath);
    if(filepath.isEmpty()){
        timer->stop();
        yPos = 0;
        this->update();
        yPos = this->height();
        upflags = 0;
        return;
    }
    switch(lvl){
    case 1:rate = 25;break;
    case 2:rate = 15;break;
    case 3:rate = 10;break;
    default:rate = 45;break;
    }
    timer->start(rate);
}

void Mouse::paintEvent(QPaintEvent *)
{
    QPainter  paint(this);
    QRect s(0, 0, img.width(), img.height());
    QRect t(0, yPos, this->width(), this->height());
    paint.drawImage(t, this->img);
}
