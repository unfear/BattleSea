#include "uimanager.h"

UIManager::UIManager(APP_ROLE role, Listener * listener)
    : QObject(),
      mWindow(role)
{
    connect(&mWindow, SIGNAL(readyToPlay()), this, SLOT(notifyReadyToPlay()));
    mWindow.setListener(listener);
}

UIManager::~UIManager()
{

}

void UIManager::drawWindow()
{
    mWindow.setupShips();
    mWindow.show();
}

void UIManager::notifyReadyToPlay()
{
    emit notifyReady();
}

void UIManager::catchEnemysFire(FireEvent eventData)
{
    mWindow.catchFireAndCheck(eventData);
}
