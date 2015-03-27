#include "networkmanager.h"

#include "client.h"
#include "server.h"
#include "socketapi.h"

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
    mContext->setStrategy(new SocketAPI);
//    mContext->runClientServer();
}

void NetworkManager::run()
{
    mContext->runClientServer();
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
    setContext(new Server);
    mRole = SERVER;
}

APP_ROLE NetworkManager::getRole() const
{
    return mRole;
}
