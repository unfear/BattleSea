#ifndef SERVER_H
#define SERVER_H

#include "context.h"

/**
 * @brief The Server class
 * does server role stuff
 */
class Server : public Context
{
public:
    Server();
    ~Server();
    virtual void setStrategy(NetworkStrategy *strategy) override;
    virtual void runClientServer() override;
    virtual void onSend(FireEvent eventData) override;
    virtual void onReceive(FireEvent eventData) override;
    virtual void setListener(Listener * listener) override;
private:
    NetworkStrategy * mStrategy;
};

#endif // SERVER_H
