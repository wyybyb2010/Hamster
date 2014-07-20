#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "mouse.h"

/*
 * 3、背景音乐（停止）
 * 6、游戏时间自定义
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setMaximumSize(550, 500);
    this->setMinimumSize(550, 500);
    curIndex = 0;
    pressIndex = curIndex + 1;
    curLevel = 0;
    ui->setupUi(this);
    startSound = new QSound(":/audio/app.wav",this);
    startSound->play(":/audio/app.wav");

    bgimg.load(":/images/bg002.png");
    ui->actionBaseMode->setIcon(QIcon(":/images/lvl01.png"));
    ui->actionMidMode->setIcon(QIcon(":/images/lvl18.png"));
    ui->actionHighMode->setIcon(QIcon(":/images/lvl21.png"));
    ui->actionCrazyMode->setIcon(QIcon(":/images/lvl04.png"));
    stopEnable();
    update();

    ui->btn0->setGeometry(91, 64, 85, 80);
    ui->btn1->setGeometry(220, 61, 85, 80);
    ui->btn2->setGeometry(355, 67, 85, 80);
    ui->btn3->setGeometry(72, 160, 85, 80);
    ui->btn4->setGeometry(221, 160, 85, 80);
    ui->btn5->setGeometry(358, 158, 85, 80);
    ui->btn6->setGeometry(69, 270, 78, 70);
    ui->btn7->setGeometry(223, 265, 80, 80);
    ui->btn8->setGeometry(372, 265, 85, 80);

    btngrp = new QButtonGroup;
    btngrp->addButton(ui->btn0, 0);
    btngrp->addButton(ui->btn1, 1);
    btngrp->addButton(ui->btn2, 2);
    btngrp->addButton(ui->btn3, 3);
    btngrp->addButton(ui->btn4, 4);
    btngrp->addButton(ui->btn5, 5);
    btngrp->addButton(ui->btn6, 6);
    btngrp->addButton(ui->btn7, 7);
    btngrp->addButton(ui->btn8, 8);

    connect(btngrp, SIGNAL(buttonClicked(int)),\
            this, SLOT(myHandlerBtn(int)));

    thread = new MyThread(this);
    connect(thread, SIGNAL(myChangeIndex(int)),\
            this, SLOT(myChangeMousePos(int)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),\
            this, SLOT(changeTimer()));

    ui->statusBar->showMessage("欢迎使用本游戏娱乐！！！！");
}

void MainWindow::clearMouse()
{
    Mouse *curMouse = qobject_cast<Mouse *>(btngrp->button(curIndex));
    if(!curMouse){
        return;
    }
    curMouse->setBackImage(" ");
}

void MainWindow::changeTimer()
{
    int val = ui->lcdNumber->intValue();
    if(val == 0){
        if(ui->lcdNumber_2->intValue() < 10){
            QSound::play(":/audio/lowend.wav");
        }else{
            QSound::play(":/audio/highend.wav");
        }
        on_actionStop_triggered();
        QMessageBox::information(this, "GameOver",
                                 tr("您的分数：%1").arg(ui->lcdNumber_2->intValue()),\
                                 QMessageBox::Ok);
        ui->statusBar->showMessage(tr("游戏结束，您的分数是：%1").arg(ui->lcdNumber_2->intValue()));
        return;
    }
    ui->lcdNumber->display(--val);
}

void MainWindow::myChangeMousePos(int pos)
{
    Mouse *posMouse = qobject_cast<Mouse *>(btngrp->button(pos));
    if(!posMouse){
        return;
    }
    clearMouse();
    posMouse->setBackImage(":/images/u03.png", curLevel);
    curIndex = pos;
}

void MainWindow::myHandlerBtn(int index)
{
    pressIndex = index;
    if(curIndex > 8 || curIndex < 0) return;
    if(index == curIndex){
        int  val = ui->lcdNumber_2->intValue();
        ui->lcdNumber_2->display(++val);
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter  painter(this);
    QRect source(0, 0, bgimg.width(), bgimg.height());
    QRect target(0, 0, this->width(), this->height());
    painter.drawImage(target, bgimg, source);
}

void MainWindow::mousePressEvent(QMouseEvent * e)
{
    e->accept();
    if(curIndex == pressIndex){
        QSound::play(":/audio/hitOn.wav");
        QCursor my(QPixmap(":/images/hitOn.png"), 0, 30);
        ui->centralWidget->setCursor(my);
        clearMouse();
        curIndex = 10;
    }else{
        QSound::play(":/audio/recvfile.wav");
        QCursor my(QPixmap(":/images/bt002.png"), 0, 30);
        ui->centralWidget->setCursor(my);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();
    QCursor my(QPixmap(":/images/bt001.png"), 0, 30);
    ui->centralWidget->setCursor(my);
}

void MainWindow::startEnable()
{
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(true);
    ui->actionBaseMode->setEnabled(false);
    ui->actionMidMode->setEnabled(false);
    ui->actionHighMode->setEnabled(false);
    ui->actionCrazyMode->setEnabled(false);
    ui->centralWidget->setEnabled(true);
}

void MainWindow::stopEnable()
{
    if(ui->lcdNumber_2->intValue() == 0){
        ui->actionStart->setEnabled(true);
    }
    ui->actionStop->setEnabled(false);
    ui->actionBaseMode->setEnabled(true);
    ui->actionMidMode->setEnabled(true);
    ui->actionHighMode->setEnabled(true);
    ui->actionCrazyMode->setEnabled(true);
    ui->centralWidget->setEnabled(false);
}

void MainWindow::on_actionStart_triggered()
{
    startSound->stop();
    if(!startSound->isFinished()){
        startSound->stop();
    }
    timer->start(1000);
    thread->start();
    startEnable();
    ui->statusBar->showMessage("游戏正在进行，挥起你的锤子吧！");
}

void MainWindow::on_actionStop_triggered()
{
    clearMouse();
    curIndex = 0;
    pressIndex = curIndex + 1;
    timer->stop();
    thread->stopMyThread();
    stopEnable();
    ui->statusBar->showMessage("游戏结束了，准备下局吧！");
}

void MainWindow::on_actionExit_triggered()
{
    on_actionStop_triggered();
    if(thread->isRunning()) thread->terminate();
    delete thread;
    if(timer->isActive()) timer->stop();
    delete timer;
    this->close();
}

void MainWindow::on_actionReset_triggered()
{
    if(thread->isRunning() || timer->isActive()){
        thread->stopMyThread();
        timer->stop();
    }
    ui->lcdNumber->display(30);
    ui->lcdNumber_2->display(0);
    stopEnable();
    clearMouse();
    ui->statusBar->showMessage("游戏已经重置，数据恢复初始值！");
}

void MainWindow::on_actionAboutGame_triggered()
{
    QMessageBox::information(this, "关于游戏",
                             "本游戏有Paul个人开发，所有解释权归本人所有"\
                             "\n如有任何问题请联系本人:(QQ)825228234"\
                             "\n本人邮箱：825228234@qq.com"\
                             "\n\nCopyRight @ 2014.7.7-2015.7.7"\
                             "\n版权所有，翻版必究，如有雷同，纯属巧合",\
                             QMessageBox::Ok);
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this, "关于Qt");
}

void MainWindow::on_actionBaseMode_triggered()
{
    thread->changeMode(BASEMODE);
    curLevel = BASEMODE;
    QMessageBox::information(this, "等级", "初级模式！", QMessageBox::Ok);
    ui->statusBar->showMessage("菜菜，您选择了基础模式！");
}

void MainWindow::on_actionMidMode_triggered()
{
    thread->changeMode(MIDMODE);
    curLevel = MIDMODE;
    QMessageBox::information(this, "等级", "中级模式！", QMessageBox::Ok);
    ui->statusBar->showMessage("小菜，您选择中级模式！");
}

void MainWindow::on_actionHighMode_triggered()
{
    thread->changeMode(HIGHMODE);
    curLevel = HIGHMODE;
    QMessageBox::information(this, "等级", "高级模式！", QMessageBox::Ok);
    ui->statusBar->showMessage("厉害，您选择了高级模式！");
}

void MainWindow::on_actionCrazyMode_triggered()
{
    thread->changeMode(CRAZYMODE);
    curLevel = CRAZYMODE;
    QMessageBox::information(this, "等级", "变态模式！", QMessageBox::Ok);
    ui->statusBar->showMessage("疯了，您选择了变态模式！");
}

void MainWindow::on_actionMusicOne_triggered()
{
    if(!startSound->isFinished())
        startSound->stop();
    startSound->play(":/audio/app.wav");
}

void MainWindow::on_actionMusicTwo_triggered()
{
    if(!startSound->isFinished())
        startSound->stop();
    startSound->play(":/audio/pzmusic.wav");
}

void MainWindow::on_actionMusicThree_triggered()
{
    if(!startSound->isFinished())
        startSound->stop();
    startSound->play(":/audio/pzmusic.wav");
}

void MainWindow::on_actionMusicFour_triggered()
{
    if(!startSound->isFinished())
        startSound->stop();
    startSound->play(":/audio/pzmusic.wav");
}

void MainWindow::on_actionMusicFive_triggered()
{
    if(!startSound->isFinished())
        startSound->stop();
    startSound->play(":/audio/pzmusic.wav");
}

void MainWindow::on_actionMusicNext_triggered()
{
    if(!startSound->isFinished())
        startSound->stop();
    startSound->play(":/audio/pzmusic.wav");
}

MainWindow::~MainWindow()
{
    delete startSound;
    delete ui;
}
