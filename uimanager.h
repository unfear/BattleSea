#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "mainwindow.h"
#include "utility.h"

class UIManager : public QObject
{
    Q_OBJECT
public:
    explicit UIManager(APP_ROLE role);
    ~UIManager();

    void drawWindow();

private:
    MainWindow mWindow;
public slots:
    void notifyReadyToPlay();
signals:
    void notifyReady();
};

#endif // UIMANAGER_H
