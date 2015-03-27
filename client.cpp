#include "client.h"

Client::Client()
{

}

Client::~Client()
{
    mStrategy->stopClient();
    delete mStrategy;
}

void Client::setStrategy(NetworkStrategy *strategy)
{
    mStrategy = strategy;
}

void Client::runClientServer()
{
    mStrategy->initSocket();
    mStrategy->runClient();
}
