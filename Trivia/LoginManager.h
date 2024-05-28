#pragma once
#include "LoggedUser.hpp"
#include "IDatabase.h"
#include <vector>
class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	LoginManager(IDatabase* database);
	~LoginManager();
	void signup(std::string name, std::string password, std::string mail);
	void login(std::string name, std::string password);
	void logout(std::string name);
};