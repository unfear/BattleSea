#include "gamemanager.h"

GameManager::GameManager()
    : mUIManager(NULL),
      mNetworkManager(new NetworkManager)
{

}

GameManager::~GameManager()
{
    delete mUIManager;
    delete mNetworkManager;
}

void GameManager::createUI()
{
    mUIManager = new UIManager(mNetworkManager->getRole());
    mUIManager->drawWindow();
}

void GameManager::setApplicationRole()
{
    mNetworkManager->setupRole();
}
