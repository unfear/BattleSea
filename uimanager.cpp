#include "uimanager.h"

UIManager::UIManager(APP_ROLE role)
    : QObject(),
      mWindow(role)
{
    connect(&mWindow, SIGNAL(readyToPlay()), this, SLOT(notifyReadyToPlay()));
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
