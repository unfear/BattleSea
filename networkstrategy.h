#ifndef NETWORKSTRATEGY
#define NETWORKSTRATEGY

#include "utility.h"
#include "listener.h"

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

    /// set listener to notify when data received and check BANG or MISS required.
    virtual void setListener(Listener * listener) = 0;
};

#endif // NETWORKSTRATEGY
