#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "LoggedUser.hpp"
struct RoomData
{
	unsigned int _RoomId;
	std::string _Name;
	unsigned int _maxPlayers;
	unsigned int _numOfQuestionsInGame;
	unsigned int _TimePerQuestion;
	unsigned int _isActive;
};
class Room
{
public:
	Room() = default;
	~Room() = default;
	bool addUser(LoggedUser user);
	bool removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	void setRoomData(const RoomData& data);
	RoomData getRoomData() const;
private:
	std::vector<LoggedUser> m_users;
	RoomData m_meatadata;
};