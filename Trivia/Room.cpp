#include "Room.h"  
#include <algorithm>  

bool Room::addUser(LoggedUser user) 
{
    auto it = std::find(m_users.begin(), m_users.end(), user);
    if (it == m_users.end()) 
    {  
        m_users.push_back(user);
        return true;
    }
    return false; 
}
bool Room::removeUser(LoggedUser user) 
{
    auto it = std::find(m_users.begin(), m_users.end(), user);
    if (it != m_users.end()) 
    { 
        m_users.erase(it); 
        return true;
    }
    return false; 
}

std::vector<std::string> Room::getAllUsers()
{
    std::vector<std::string> usernames;
    for (auto& user : m_users) 
    { 
        usernames.push_back(user.getUsername());
    }
    return usernames;
}
void Room::setRoomData(const RoomData& data) 
{
    m_meatadata = data;
}

RoomData Room::getRoomData() const 
{
    return m_meatadata;
}