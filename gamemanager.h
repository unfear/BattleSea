#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "uimanager.h"
#include "networkmanager.h"
#include "listener.h"

/**
 * @brief The GameManager class
 * creates UI and set role of app (client or server)
 */
class GameManager : public QObject, public Listener
{
    Q_OBJECT
public:
    GameManager();

    ~GameManager();

    /// Create main window and battlefield
    void createUI();

    /// Become Client or Server
    void setApplicationRole();

    /// notify send data
    void onSendData(FireEvent eventData) override;

    /// notify receive data
    void onReceiveData(FireEvent eventData) override;

private:
    UIManager       *mUIManager;
    NetworkManager  *mNetworkManager;

public slots:
    /// start client/server
    void runClientServer();
};

#endif // GAMEMANAGER_H
