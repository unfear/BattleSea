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

void Client::onSend(FireEvent eventData)
{
    mStrategy->sendData(eventData);
}

void Client::onReceive(FireEvent eventData)
{

}

void Client::setListener(Listener * listener)
{
    mStrategy->setListener(listener);
}
