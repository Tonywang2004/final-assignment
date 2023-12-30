// Server.h
#pragma once
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include "RoomManager.h"
#pragma comment(lib, "ws2_32.lib")
class TCPServer {
public:
	TCPServer();
	void createroom(SOCKET clientSocket);
	void AcceptConnection();
	void HandleClient(SOCKET clientSocket);
	void updateRoomInfo(int id);
	~TCPServer();
private:
	WSADATA wsaData;
	SOCKET serverSocket;
	sockaddr_in serverAddr;
	std::unique_ptr<RoomManager> roomManager;
};