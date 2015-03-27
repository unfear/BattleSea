#ifndef CLIENT_H
#define CLIENT_H

#include "context.h"

/**
 * @brief The Client class
 * does client role stuff
 */
class Client : public Context
{
public:
    Client();
    virtual ~Client();
    virtual void setStrategy(NetworkStrategy *strategy) override;
    virtual void runClientServer() override;
private:
    NetworkStrategy * mStrategy;
};

#endif // CLIENT_H
