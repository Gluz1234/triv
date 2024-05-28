#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database):m_database(database)
{
}

LoginManager::~LoginManager()
{
	this->m_loggedUsers.clear();
}

void LoginManager::signup(std::string name, std::string password, std::string mail)
{
    if (m_database->doesUserExist(name))
    {
        throw ("User is exist");
    }
    else
    {
        m_database->addNewUser(name, password, mail);
    }
}

void LoginManager::login(std::string name, std::string password)
{
    if (!m_database->doesUserExist(name) || !m_database->doesPasswordMatch(name, password))
    {
        throw ("Failed info, try again");
    }
    else
    {
        m_loggedUsers.push_back(LoggedUser(name));
    }
}

void LoginManager::logout(std::string name)
{
    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); )
    {
        if (it->getUsername() == name)
        {
            it = m_loggedUsers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
