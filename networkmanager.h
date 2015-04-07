#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "context.h"
#include "utility.h"

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    /// setup role of the app.
    void setupRole(Listener * listener);

    /// get client or server role
    APP_ROLE getRole() const;

    /// run client/server
    void run();

    /// send data callback
    void onSend(FireEvent eventData);

    /// receive data callback
    void onReceive(FireEvent eventData);

private:
    /// set Client/Server context
    void setContext(Context * context);

    /// set listener
    void setListener(Listener * listener);

    Context *   mContext;
    APP_ROLE    mRole;
};

#endif // NETWORKMANAGER_H
