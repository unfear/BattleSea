#include "uimanager.h"

UIManager::UIManager()
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
