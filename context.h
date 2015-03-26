#ifndef CONTEXT_H
#define CONTEXT_H

#include "networkstrategy.h"

class Context
{
public:
    /// destroy correct
    virtual ~Context(){}
    /// select Socket API or QNetwork API interface
    virtual void setStrategy(NetworkStrategy* strategy) = 0;
};

#endif // CONTEXT_H
