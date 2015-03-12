#include "uimanager.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::drawWindow()
{
    mWindow.openImage(":/images/images/ship1h.png");
    mWindow.setupShips();
    mWindow.show();
}
