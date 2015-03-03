#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QWidget>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.openImage(":/images/images/ship1h.png");
    w.setupShips();
    w.show();
    
    return a.exec();
}
