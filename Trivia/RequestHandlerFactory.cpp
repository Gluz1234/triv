#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
	m_database(database), m_loginManager(LoginManager(database)), m_StatisticsManager(database)
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_database;
	m_database = nullptr;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
	return new MenuRequestHandler(*this, user);
}
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}
