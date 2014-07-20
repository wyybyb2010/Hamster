#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
//    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QApplication a(argc, argv);
    a.setApplicationName("LovelyGame");
    a.setWindowIcon(QIcon(":/images/bt02.png"));

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/bt02.png"));
    w.show();

    return a.exec();
}
