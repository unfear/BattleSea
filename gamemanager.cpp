#include "gamemanager.h"

GameManager::GameManager()
    : QObject(),
      mUIManager(NULL),
      mNetworkManager(new NetworkManager)
{

}

GameManager::~GameManager()
{
    delete mUIManager;
    delete mNetworkManager;
}

void GameManager::runClientServer()
{
    mNetworkManager->run();
}

void GameManager::createUI()
{
    mUIManager = new UIManager(mNetworkManager->getRole());
    mUIManager->drawWindow();
    connect(mUIManager, SIGNAL(notifyReady()), this, SLOT(runClientServer()));
}

void GameManager::setApplicationRole()
{
    mNetworkManager->setupRole();
}
