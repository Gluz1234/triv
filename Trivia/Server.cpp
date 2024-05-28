#include "Server.h"
#include "Communicator.h"
Server::Server(std::string& ip, int port, IDatabase* database) : _ip(ip), _port(port), m_database(database),
m_hadlerFactory(RequestHandlerFactory(database)), m_communicator(Communicator(m_hadlerFactory))
{
}

Server::~Server()
{
}

void Server::run() {
	std::thread t = std::thread(&Communicator::startHandleRequests, m_communicator, _ip, _port);
	t.detach();
	std::string message;
	do
	{
		std::getline(std::cin, message);
	} while (!message.compare("EXIT"));
}