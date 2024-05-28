#include "RoomManager.h"
bool RoomManager::createRoom(const LoggedUser& creator, const RoomData& roomData) 
{
   
    if (this->m_rooms.find(roomData._RoomId) != this->m_rooms.end())
    {
        return false;
    }
    Room newRoom;
    newRoom.addUser(creator);  
    newRoom.setRoomData(roomData);
    this->m_rooms[roomData._RoomId] = newRoom;
    return true;
}
bool RoomManager::deleteRoom(int roomId) 
{
    auto it = this->m_rooms.find(roomId);
    if (it != this->m_rooms.end())
    {
        this->m_rooms.erase(it);
        return true;
    }
    return false;
}
unsigned int RoomManager::getRoomState(int roomId) const 
{
    auto it = this->m_rooms.find(roomId);
    if (it != this->m_rooms.end()) 
    {
        return it->second.getRoomData()._isActive;  
    }
    throw std::runtime_error("Room not found");
}

std::vector<RoomData> RoomManager::getRooms() const 
{
    std::vector<RoomData> roomList;
    for (const auto& pair : m_rooms) 
    {
        roomList.push_back(pair.second.getRoomData()); 
    }
    return roomList;
}
Room& RoomManager::getRoom(int roomId)
{
    auto it = m_rooms.find(roomId);
    if (it != m_rooms.end()) 
    {
        return it->second;  
    }
    throw std::runtime_error("Room not found");
}