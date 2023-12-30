#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "GameClient.h"
using namespace std;
TCPClient::TCPClient() {
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(55555);  // 连接端口 55555
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // 连接本地服务器

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
}

void TCPClient::SendMessage(const char* message) {
    send(clientSocket, message, strlen(message), 0);
    std::cout << "Message sent!" << std::endl;
}
void TCPClient::receive() {
    char recvBuffer[1024]; // 接收消息的缓冲区
    int result;
    result = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
    if (result > 0) {
        std::cout << "Message received: " << recvBuffer << std::endl;
    }
    else if (result == 0) {
        std::cout << "Connection closed." << std::endl;
    }
    else {
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
    }
}
TCPClient::~TCPClient() {
    closesocket(clientSocket);
    WSACleanup();
}
