#ifndef NETWORKSTRATEGY
#define NETWORKSTRATEGY

#include "utility.h"

class NetworkStrategy
{
public:
    virtual ~NetworkStrategy(){}
    /// initialize socket
    virtual void initSocket() = 0;
    virtual bool runClient() = 0;
    virtual void stopClient() = 0;
    virtual bool runServer() = 0;
    virtual void stopServer() = 0;
    virtual void sendData(FireEvent event) = 0;
    virtual void receiveData() = 0;
    virtual APP_ROLE getRole() = 0;
};

#endif // NETWORKSTRATEGY
