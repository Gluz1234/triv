#include "RequestHandlerFactory.h"
#include "IDatabase.h"
#include "Communicator.h"
class Server
{
public:
	Server(std::string& ip, int port, IDatabase* database);
	~Server();
	void run();

private:
	int _port;
	Communicator m_communicator;
	std::string _ip;
	RequestHandlerFactory m_hadlerFactory;
	IDatabase* m_database;
};