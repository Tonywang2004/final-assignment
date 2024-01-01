#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
//客户端代码
class TCPClient {
public:
    TCPClient();//构造函数，无参数 

    void SendMessage(const char* message);//发送消息 
    void receive();//接受消息 
    ~TCPClient();//析构函数 
private:
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
};
