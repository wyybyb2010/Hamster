#ifndef MOUSE_H
#define MOUSE_H

#include <QAbstractButton>
#include <QPainter>
#include <QRect>
#include <QImage>
#include <QString>
#include <QTimer>

class Mouse : public QAbstractButton
{
    Q_OBJECT
public:
    Mouse(QWidget *parent = 0);
    void  setBackImage(QString, int lvl = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);

public slots:
    void  flyUpImage();

private:
    QImage      img;
    QTimer      *timer;
    int         upflags;
    int         yPos;
    int         rate;

};

#endif // MOUSE_H
