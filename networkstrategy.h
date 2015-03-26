#ifndef NETWORKSTRATEGY
#define NETWORKSTRATEGY

class NetworkStrategy
{
public:
    /// initialize socket
    virtual void initSocket() = 0;
    virtual void runClient() = 0;
    virtual void stopClient() = 0;
    virtual void runServer() = 0;
    virtual void stopServer() = 0;
    virtual void sendData() = 0;
    virtual void receiveData() = 0;
};

#endif // NETWORKSTRATEGY