#ifndef SOCKETAPI_H
#define SOCKETAPI_H

#include "networkstrategy.h"

class SocketAPI : public NetworkStrategy
{
public:
    SocketAPI();
    virtual ~SocketAPI();
    virtual void initSocket() override;
    virtual void runClient() override;
    virtual void stopClient() override;
    virtual void runServer() override;
    virtual void stopServer() override;
    virtual void sendData() override;
    virtual void receiveData() override;
};

#endif // SOCKETAPI_H
