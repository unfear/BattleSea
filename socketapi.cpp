#include "socketapi.h"
#include "utility.h"
#include <unistd.h>
#include <sstream>
#include <string>

bool SocketAPI::mCtrlCSig = false;
int SocketAPI::mCountThreadCalls = 0;

SocketAPI::SocketAPI()
    : mPort(0),
      mHost(""),
      mSocket(0),
      mListener(nullptr)
{
}

SocketAPI::~SocketAPI()
{
    if(close(mSocket) != 0)
        cout << "Error Socket close connection!" << endl;
    else
        cout << "SUCCESSFULLY Socket close connection!" << endl;
}

void SocketAPI::initSocket()
{
    if(mSocket != 0) return;

    mPort = 9999;
    mHost = "127.0.0.1";
    mCtrlCSig = false;
    mCountThreadCalls = 0;

    // UDP connection
    mSocket = socket(PF_INET, SOCK_DGRAM, 0);
    cout << "Socket descriptor: " << mSocket << endl;

    memset(&mDest, 0x0, sizeof(mDest));
    mDest.sin_family = AF_INET;
    mDest.sin_port = htons(mPort);

    // catch signals
    struct sigaction act;
    memset(&act, 0x0, sizeof(act));
    act.sa_handler = signalCatcher;
    sigaction(SIGINT, &act, 0);
}

bool SocketAPI::runClient()
{
    cout << "Program works in Client mode!" << endl;

    inet_aton(mHost.c_str(), &mDest.sin_addr);
    if(connect(mSocket, (struct sockaddr *)&mDest, sizeof(mDest)) != 0)
    {
        cout << "Error Socket connection!" << endl;
        close(mSocket);
        return false;
    }

    return true;
}

void SocketAPI::stopClient()
{
    mCtrlCSig = true;
}

bool SocketAPI::runServer()
{
    cout << "Program works in Server mode!" << endl;

    mDest.sin_addr.s_addr = INADDR_ANY;
    if ( bind(mSocket, (struct sockaddr *)&mDest, sizeof(mDest)) != 0 )
    {
        cout << "Error Socket bind!" << endl;
        close(mSocket);
        return false;
    }

    // create thread
    pthread_t pchild;
    if(pthread_create(&pchild, 0, serverChildThreadFunc, this) != 0)
    {
        cout << "Thread create Error!" << endl;
    }

    pthread_detach(pchild);
    return true;
}

void SocketAPI::stopServer()
{
    mCtrlCSig = true;
}

void SocketAPI::sendData(FireEvent event)
{
    std::stringstream ss;
    ss << event;
    cout << "Send to server:" << ss.str().c_str() << " len:" << ss.str().length() << endl;
    send(mSocket, ss.str().c_str(), ss.str().size(), 0);
}

void SocketAPI::receiveData()
{

}

APP_ROLE SocketAPI::getRole()
{
    initSocket();
    runClient();
    FireEvent event{0, 0, SEND_EVENT::UNKNOWN_EVENT};
    sendData(event);

    char buf[100];
    memset(buf, 0, sizeof(buf));
    //Receive a reply from the server
    cout << "waiting for reply..." << endl;
    recv(mSocket, buf, sizeof(buf)-1, 0);

    if( strcmp(buf, "client") != 0)
    {
        cout << "replyed:" << buf << endl;
        stopClient();
        return SERVER;
    }
    else
    {
        cout << "replyed:" << buf << endl;
        stopClient();
        return CLIENT;
    }

    stopClient();
    return SERVER;
}

void SocketAPI::signalCatcher(int)
{
    mCtrlCSig = true;
    cout << "quit" << endl;;
}

void* SocketAPI::serverChildThreadFunc(void* data)
{
    cout << "Started server in thread" << endl;
    SocketAPI * appData = static_cast<SocketAPI*>(data);
    int bytes = 0;
    char buffer[1024]; // FIXME: replace buffer by mMessageBuffer

    do
    {
        int addrLen=sizeof(appData->mDest);
        bzero(buffer, sizeof(buffer));
        cout << "waiting for msg" << endl;
        bytes = recvfrom(appData->mSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&(appData->mDest), (socklen_t*)&addrLen);
        cout << "msg from client:" << buffer << " bytes:" << bytes << endl;
        cout << "countThreadCalls: " <<  appData->mCountThreadCalls << endl;
        std::stringstream ssResult;
        std::string tempStr(buffer);
        ssResult << tempStr;
        FireEvent event;
        ssResult >> event;
        cout << "msg from client:" << event.x << " " << event.y << " " << (int)event.event << " bytes:" << bytes << endl;
        if(event.event == SEND_EVENT::UNKNOWN_EVENT) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "client");
            sendto(appData->mSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&(appData->mDest), (socklen_t)addrLen);
            cout << "reply: " << buffer << " to socket: " << appData->mSocket << endl;
        }
        else if(event.event == SEND_EVENT::FIRE) {
            appData->mListener->onReceiveData(event);
        }

    }while( bytes > 0 && strcmp(buffer, "quit") != 0);

    appData->mCtrlCSig = true;
}

void SocketAPI::setListener(Listener * listener)
{
    mListener = listener;
}
