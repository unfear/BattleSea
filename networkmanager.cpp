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

void NetworkManager::setListener(Listener * listener)
{
    mContext->setListener(listener);
}

void NetworkManager::run()
{
    mContext->runClientServer();
}

void NetworkManager::setupRole(Listener * listener)
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
    setListener(listener);
}

APP_ROLE NetworkManager::getRole() const
{
    return mRole;
}

void NetworkManager::onSend(FireEvent eventData)
{
    mContext->onSend(eventData);
}

void NetworkManager::onReceive(FireEvent eventData)
{

}
