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
