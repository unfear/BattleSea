#include "server.h"

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
