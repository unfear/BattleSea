#include "uimanager.h"

UIManager::UIManager(APP_ROLE role)
    :mWindow(role)
{

}

UIManager::~UIManager()
{

}

void UIManager::drawWindow()
{
    mWindow.setupShips();
    mWindow.show();
}
