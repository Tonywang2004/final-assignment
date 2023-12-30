#pragma once
// Room.h
#include <vector>
#include "player.h"

class Room {
public:
    Room(int id) : id(id) {}

    
    int getId() const {
        return id;
    }
    
    // 其他方法，如移除玩家、获取房间信息等
    // 其他管理方法，如删除房间等
    void AddPlayer(const std::shared_ptr<Player>& player) {
        if (players_.size() < 4) {
            players_.push_back(player);
        }
        
    }
    // 获取房间中的玩家数目
    size_t GetPlayerCount() const {
        return players_.size();
    }
    //获取玩家
    std::vector<std::string> GetAllPlayerNames() const {
        std::vector<std::string> names;
        for (const auto& player : players_) {
            names.push_back(player->getName());
        }
        return names;
    }
    // 从房间移除玩家
    void RemovePlayer(const std::shared_ptr<Player>& player) {
        players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());
    }

    

private:
    int id;
    std::vector<std::shared_ptr<Player>> players_;
    std::unordered_map<int, std::shared_ptr<Room>> rooms_;
};
