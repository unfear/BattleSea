#ifndef QTNETWORK_H
#define QTNETWORK_H

#include "networkstrategy.h"

class QtNetwork : public NetworkStrategy
{
public:
    QtNetwork();
    virtual ~QtNetwork();
    virtual void initSocket() override;
    virtual bool runClient() override;
    virtual void stopClient() override;
    virtual bool runServer() override;
    virtual void stopServer() override;
    virtual void sendData() override;
    virtual void receiveData() override;
};

#endif // QTNETWORK_H
