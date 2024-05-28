#pragma once
#include <iostream>
#include "LoggedUser.hpp"
#include "LoginManager.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"
class LoginRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
	IDatabase* m_database;
};