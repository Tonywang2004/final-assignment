#include "Server.h"

TCPServer::TCPServer() {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(55555);  // 监听端口 55555
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, 5);
}

void TCPServer::AcceptConnection() {
	SOCKET clientSocket;
	sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);

	while (true) {
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if (clientSocket != INVALID_SOCKET) {
			std::cout << "Client connected!" << std::endl;
			// 这里可以启动一个新线程来处理客户端的数据
			//std::thread clientThread(&TCPServer::HandleClient, this, clientSocket);
			//clientThread.detach();  // 将线程分离，使其在后台运行
			std::thread clientThread(&TCPServer::createroom, this, clientSocket);
			clientThread.detach();  // 将线程分离，使其在后台运行
		}
	}
}
void TCPServer::HandleClient(SOCKET clientSocket) {
	// 在这里处理来自客户端的数据
	char buffer[1024];
	while (true) {
		int bytesReceived = recv(clientSocket, buffer, 1024, 0);
		if (bytesReceived <= 0) break; // 客户端断开连接或发生错误

		// 输出接收到的数据
		std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;

		// 发送响应（如果需要）
		// ...
	}

	closesocket(clientSocket);  // 关闭客户端套接字
}
void TCPServer::createroom(SOCKET clientSocket)
{
	char buffer[1024];
	while (true) {
		int bytesReceived = recv(clientSocket, buffer, 1024, 0);
		if (bytesReceived <= 0) break; // 客户端断开连接或发生错误

		// 输出接收到的数据
		//std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;
		std::string receivedData(buffer, bytesReceived);
		// 基于接收到的数据创建玩家
		
		//auto player = std::make_shared<Player>(clientSocket, receivedData);
		//获取房间ID
		int room_number = std::stoi(buffer);
		//初始化房间管理器
		roomManager = std::make_unique<RoomManager>();
		//先查找房间号
		auto foundRoom = roomManager->getRoom(room_number);
		if (foundRoom == nullptr) {
			//创建房间
			auto room = roomManager->createRoom(room_number);
			//添加玩家
			size_t player_count = room->GetPlayerCount() + 1;//记录玩家数
			std::string str1 = "Player";
			std::string str2 = std::to_string(player_count);
			std::string str = str1 + str2;
			auto player = std::make_shared<Player>(clientSocket, str);
			room->AddPlayer(player);
		}
		else {
			//添加玩家
			size_t player_count = foundRoom->GetPlayerCount() + 1;//记录玩家数
			std::string str1 = "Player";
			std::string str2 = std::to_string(player_count);
			std::string str = str1 + str2;
			auto player = std::make_shared<Player>(clientSocket, str);
			foundRoom->AddPlayer(player);
		}
		
		updateRoomInfo(room_number);
		// 发送响应（如果需要）
		// ...
	}
	
	closesocket(clientSocket);
	
}
void TCPServer::updateRoomInfo(int id) {
	Room* room1 = roomManager->getRoom(id); // 显示房间ID
	
	if (room1) { 
		std::string roomInfo = "Room ID: " + std::to_string(room1->getId());
		std::cout << roomInfo << std::endl;
		std::string playerList = "Players:\n";
		std::cout << "Player name: " << std::endl;
		std::vector<std::string> playerNames = room1->GetAllPlayerNames();
		for (const auto& name : playerNames) {
			std::cout << name << std::endl;
		}
		
	}
}
TCPServer::~TCPServer() {
	closesocket(serverSocket);
	WSACleanup();
}