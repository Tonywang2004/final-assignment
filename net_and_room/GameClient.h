#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class TCPClient {
public:
    TCPClient();

    void SendMessage(const char* message);
    void receive();
    ~TCPClient();
private:
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
};