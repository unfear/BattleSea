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
    mUIManager = new UIManager(mNetworkManager->getRole(), this);
    mUIManager->drawWindow();
    connect(mUIManager, SIGNAL(notifyReady()), this, SLOT(runClientServer()));
}

void GameManager::setApplicationRole()
{
    mNetworkManager->setupRole(this);
}

void GameManager::onSendData(FireEvent eventData)
{
    mNetworkManager->onSend(eventData);
}

void GameManager::onReceiveData(FireEvent eventData)
{
    mUIManager->catchEnemysFire(eventData);
}
