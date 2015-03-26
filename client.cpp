#include "client.h"

Client::Client()
{

}

Client::~Client()
{
    delete mStrategy;
}

void Client::setStrategy(NetworkStrategy *strategy)
{
    mStrategy = strategy;
}
