#pragma once
#include <iostream>

class LoggedUser
{
private:
	std::string m_username;
public:
	std::string getUsername()
	{
		return m_username;
	}
	LoggedUser(std::string username)
	{
		m_username = username;
	}
	friend bool operator==(const LoggedUser& lhs, const LoggedUser& rhs)
	{
		return lhs.m_username == rhs.m_username;
	}
};