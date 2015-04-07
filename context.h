#ifndef CONTEXT_H
#define CONTEXT_H

#include "networkstrategy.h"
#include "listener.h"

class Context
{
public:
    /// destroy correct
    virtual ~Context(){}

    /// select Socket API or QNetwork API interface
    virtual void setStrategy(NetworkStrategy* strategy) = 0;

    /// run client or server
    virtual void runClientServer() = 0;

    /// send data callback
    virtual void onSend(FireEvent eventData) = 0;

    /// receive data callback
    virtual void onReceive(FireEvent eventData) = 0;

    /// set listener
    virtual void setListener(Listener * listener) = 0;
};

#endif // CONTEXT_H
