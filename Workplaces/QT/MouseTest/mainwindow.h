#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMessageBox>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QSound>
#include "mouse.h"

#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void  startEnable();
    void  stopEnable();
    void  clearMouse();
protected:
    void  paintEvent(QPaintEvent *);
    void  mousePressEvent(QMouseEvent*);
    void  mouseReleaseEvent(QMouseEvent*);

public slots:
    void  myHandlerBtn(int);
    void  myChangeMousePos(int);
    void  changeTimer();

    void  on_actionStart_triggered();
    void  on_actionStop_triggered();
    void  on_actionExit_triggered();
    void  on_actionReset_triggered();
    void  on_actionAboutGame_triggered();
    void  on_actionAboutQt_triggered();

    void  on_actionBaseMode_triggered();
    void  on_actionMidMode_triggered();
    void  on_actionHighMode_triggered();
    void  on_actionCrazyMode_triggered();

    void  on_actionMusicOne_triggered();
    void  on_actionMusicTwo_triggered();
    void  on_actionMusicThree_triggered();
    void  on_actionMusicFour_triggered();
    void  on_actionMusicFive_triggered();
    void  on_actionMusicNext_triggered();

private:
    Ui::MainWindow *ui;
    QImage         bgimg;
    QButtonGroup   *btngrp;
    int            curIndex;
    int            pressIndex;
    int            curLevel;
    QTimer         *timer;
    MyThread       *thread;
    QSound         *startSound;
};

#endif // MAINWINDOW_H
