#pragma once
#include <iostream>
#include <vector>
#include <string>
// 假设有一个 Player 类
class Player0
{
public:
    Player0(int id, std::string name) : id(id), name(std::move(name)) {}
    int getId() const { return id; }                    // 获取玩家ID
    const std::string &getName() const { return name; } // 获取玩家名字

private:
    int id;
    std::string name;
};

// Room 类定义
class Room
{
private:
    int id;                       // 房间的ID
    std::vector<Player0> players; // 房间中的玩家

public:
    // 构造函数
    Room(int id) : id(id) {}

    bool addPlayer(const Player0 &player)
    {
        if (players.size() < 4)
        { // 限制房间为4人
            players.push_back(player);
            return true;
        }
        return false;
    }
    const std::vector<Player0> &getPlayers() const
    {
        return players;
    }

    // 获取房间ID
    int getId() const
    {
        return id;
    }
};