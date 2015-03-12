#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "uimanager.h"
#include "networkmanager.h"

/**
 * @brief The GameManager class
 * creates UI and set role of app (client or server)
 */
class GameManager
{
public:
    GameManager();
    ~GameManager();

    /// Create main window and battlefield
    void createUI();

    /// Become Client or Server
    void setApplicationRole();

private:
    UIManager mUIManager;
};

#endif // GAMEMANAGER_H
