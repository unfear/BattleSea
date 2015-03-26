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
private:
    NetworkStrategy * mStrategy;
};

#endif // SERVER_H
