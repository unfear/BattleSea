#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "mainwindow.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();

    void drawWindow();

private:
    MainWindow mWindow;

};

#endif // UIMANAGER_H
