#pragma once
// Player.h
#include <string>
class Player {
public:
    Player(SOCKET socket, const std::string& name) : socket_(socket), name_(name) {}

    SOCKET getSocket() const { return socket_; }
    std::string getName() const { return name_; }

private:
    SOCKET socket_;
    std::string name_;
};
