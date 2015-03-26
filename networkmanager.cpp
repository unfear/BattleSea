#include "networkmanager.h"

#include "client.h"
#include "server.h"

NetworkManager::NetworkManager()
    : mContext(nullptr),
      mRole(UNKNOWN)
{

}

NetworkManager::~NetworkManager()
{
    delete mContext;
}

void NetworkManager::setContext(Context * context)
{
    mContext = context;
}

void NetworkManager::setupRole()
{
    // TODO: Asquire role
    // ....
    // bool client = ...

    /*
    if(client) {
        setContext(new Client);
    }
    else {
        setContext(new Server);
    }
    */
    mRole = UNKNOWN;
}

APP_ROLE NetworkManager::getRole() const
{
    return mRole;
}
