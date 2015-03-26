#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "mainwindow.h"
#include "utility.h"

class UIManager
{
public:
    explicit UIManager(APP_ROLE role);
    ~UIManager();

    void drawWindow();

private:
    MainWindow mWindow;

};

#endif // UIMANAGER_H
