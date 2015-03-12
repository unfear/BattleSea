#include <QApplication>
#include "mainwindow.h"
#include "gamemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameManager game;
    game.setApplicationRole();
    game.createUI();

    return a.exec();
}
