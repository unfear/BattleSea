#include "server.h"
#include "utility.h"

Server::Server()
{

}

Server::~Server()
{
    delete mStrategy;
}

void Server::setStrategy(NetworkStrategy *strategy)
{
    mStrategy = strategy;
}

void Server::runClientServer()
{
    cout << "RUN SERVER" << endl;
    mStrategy->initSocket();
    mStrategy->runServer();
}

void Server::onSend(FireEvent eventData)
{
    mStrategy->sendData(eventData);
}

void Server::onReceive(FireEvent eventData)
{

}

void Server::setListener(Listener * listener)
{
    mStrategy->setListener(listener);
}
