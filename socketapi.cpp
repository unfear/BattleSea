#include "socketapi.h"
#include "utility.h"
#include <unistd.h>

bool SocketAPI::mCtrlCSig = false;
int SocketAPI::mCountThreadCalls = 0;

SocketAPI::SocketAPI()
    : mPort(0),
      mHost("")
{
}

SocketAPI::~SocketAPI()
{
    if(close(mSocket) != 0)
        cout << "Error Socket close connection!" << endl;
}

void SocketAPI::initSocket()
{
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


//    pthread_join(pchild, 0);
    pthread_detach(pchild);
    return true;
}

void SocketAPI::stopServer()
{
    mCtrlCSig = true;
}

void SocketAPI::sendData()
{

}
void SocketAPI::receiveData()
{

}

void SocketAPI::signalCatcher(int)
{
    mCtrlCSig = true;
    cout << "quit" << endl;;
}

void* SocketAPI::serverChildThreadFunc(void* data)
{
    SocketAPI * appData = static_cast<SocketAPI*>(data);
    int bytes = 0;
    char buffer[1024]; // FIXME: replace buffer by mMessageBuffer
    do
    {
        int addrLen=sizeof(appData->mDest);
        bzero(buffer, sizeof(buffer));
        bytes = recvfrom(appData->mSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&(appData->mDest), (socklen_t*)&addrLen);
        cout << "msg from client:" << buffer << " bytes:" << bytes << endl;
        cout << "countThreadCalls: " <<  appData->mCountThreadCalls << endl;
    }while( bytes > 0 && strcmp(buffer, "quit") != 0);

    appData->mCtrlCSig = true;

//    do
//    {
//        cout << "Waiting for data from client...\n" << endl;
//        mCountThreadCalls++;
//        sleep(5);
//    } while(mCtrlCSig != true);
}
