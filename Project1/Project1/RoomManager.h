#pragma once
// RoomManager.h
#include <unordered_map>
#include "room.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <WinSock2.h>
class RoomManager {
public:
    Room* createRoom(int roomId) {
        //int roomId = nextRoomId++;
        auto room = new Room(roomId);
        rooms[roomId] = room;
        return room;
    }

    Room* getRoom(int roomId) {
        if (rooms.find(roomId) != rooms.end()) {
            return rooms[roomId];
        }
        return nullptr;
    }

    

private:
    int nextRoomId = 1;
    std::unordered_map<int, Room*> rooms;
    //std::vector<SOCKET> clients_;
};
