#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
private:
	std::map<unsigned int, Room> m_rooms;
public:
	RoomManager() = default;
	~RoomManager() = default;
	bool createRoom(const LoggedUser& user, const RoomData& DataRoom);
	bool deleteRoom(int ID);
	unsigned int getRoomState(int ID) const;
	std::vector<RoomData> getRooms() const;
	Room& getRoom(int ID);
};
