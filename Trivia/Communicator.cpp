#include "Communicator.h"
#include <WinSock.h>
#define SIZE 6 //size of the message
#define TEMP "Hello"
Communicator::Communicator(RequestHandlerFactory& factory) : m_handlerFactory(factory)
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		closesocket(m_serverSocket);
	}
	catch (...) {}
}
//the listing function for clients
void Communicator::bindAndListen(const std::string& ip, int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); 
	sa.sin_family = AF_INET;   
	inet_pton(AF_INET, ip.c_str(), &sa.sin_addr.s_addr); 

	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted!" << std::endl;
		LoginRequestHandler* clientHandler = m_handlerFactory.createLoginRequestHandler();
		m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, clientHandler));
		std::thread t = std::thread(&Communicator::handleNewClient, this, client_socket);
		t.detach();
	}
}
//handling the client
void Communicator::handleNewClient(SOCKET socket)
{
	try
	{
		IRequestHandler* handler = m_clients[socket];
		RequestInfo reqInfo;
		RequestResult reqRes;
		std::vector<unsigned char> buffer;
		do
		{
			reqInfo = Helper::getUserRequestInfo(socket);
			reqRes = handler->RequestHandler(reqInfo);
			buffer = reqRes.resBuffer;
			Helper::sendData(socket, buffer);
		} while (reqInfo.id != RequestId::MT_EXIT);

		closesocket(socket);
		std::cout << "client has disconnected!" << std::endl;

	}
	catch (const std::exception& e)
	{
		closesocket(socket);
		std::cout << "client has disconnected!" << std::endl;
	}
}

//just the start function
void Communicator::startHandleRequests(std::string ip, int port)
{
	bindAndListen(ip, port);
}
