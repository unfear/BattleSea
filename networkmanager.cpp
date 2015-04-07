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
}

void NetworkManager::run()
{
    mContext->runClientServer();
}

void NetworkManager::setupRole()
{
    SocketAPI tmpStratedy;
    if(tmpStratedy.getRole() == CLIENT) {
        cout << "ROLE IS CLIENT" << endl;
        setContext(new Client);
        mRole = CLIENT;
    }
    else {
        cout << "ROLE IS SERVER" << endl;
        setContext(new Server);
        mRole = SERVER;
    }
}

APP_ROLE NetworkManager::getRole() const
{
    return mRole;
}
