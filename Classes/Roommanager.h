#include <unordered_map>
#include "room.h"

class RoomManager
{
public:
    // 创建房间
    Room *createRoom(int roomId)
    {
        Room *room = new Room(roomId);
        rooms[roomId] = room;
        return room;
    }

    // 搜索房间
    Room *getRoom(int roomId)
    {
        if (rooms.find(roomId) != rooms.end())
        {
            return rooms[roomId];
        }
        return nullptr;
    }

private:
    std::unordered_map<int, Room *> rooms;
};