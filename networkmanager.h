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
    void setupRole();
    /// get client or server role
    APP_ROLE getRole() const;

private:
    /// set Client/Server context
    void setContext(Context * context);

    Context *   mContext;
    APP_ROLE    mRole;
};

#endif // NETWORKMANAGER_H
