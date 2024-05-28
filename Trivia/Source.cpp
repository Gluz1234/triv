#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.h"
#include <string>
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "SqliteDatabase.h"

int main()
{
	WSAInitializer wsaInit;

	SqliteDatabase* db = new SqliteDatabase();
	db->open();
	std::string ip = "127.0.0.1";
	std::string port = "200";

	Server myServer(ip, stoi(port), db);

	try
	{
		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occurred: " << e.what() << std::endl;
	}
	return 0;
}