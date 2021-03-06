#ifndef SOCKETAPI_H
#define SOCKETAPI_H

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <resolv.h>
#include <string>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <pthread.h>

#include "networkstrategy.h"
#include "listener.h"

class SocketAPI : public NetworkStrategy
{
public:
    SocketAPI();
    virtual ~SocketAPI();
    virtual void initSocket() override;
    virtual bool runClient() override;
    virtual void stopClient() override;
    virtual bool runServer() override;
    virtual void stopServer() override;
    virtual void sendData(FireEvent event) override;
    virtual void receiveData() override;
    virtual APP_ROLE getRole() override;
    virtual void setListener(Listener * listener) override;
private:
    /// runable func for pthread_create. Waits for msg from client
    static void* serverChildThreadFunc(void* arg);
    /// catch ctrl+C signal
    static void signalCatcher(int sig);

    int mPort;
    int mSocket;
    std::string mHost;
    std::string mMessageBuffer;
    struct sockaddr_in mDest;
    Listener * mListener; /// Shouldn't be deleted

    static bool mCtrlCSig;
    static int mCountThreadCalls;
};

#endif // SOCKETAPI_H
