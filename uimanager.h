#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "mainwindow.h"
#include "utility.h"
#include "listener.h"

class UIManager : public QObject
{
    Q_OBJECT
public:
    explicit UIManager(APP_ROLE role, Listener * listener);
    ~UIManager();

    /// draw prepared window
    void drawWindow();

    /// catch enemy's fire and check whether miss or bang.
    void catchEnemysFire(FireEvent eventData);

private:
    MainWindow mWindow;
public slots:
    void notifyReadyToPlay();
signals:
    void notifyReady();
};

#endif // UIMANAGER_H
