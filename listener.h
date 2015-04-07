#ifndef LISTENER_H
#define LISTENER_H

#include "utility.h"

/**
 * @brief The Listener class.
 * Notified GameManager when data need to send or receive.
 */
class Listener
{
public:
    virtual ~Listener(){}

    /// send data
    virtual void onSendData(FireEvent eventData) = 0;

    /// receive data
    virtual void onReceiveData(FireEvent eventData) = 0;
};

#endif // LISTENER_H
