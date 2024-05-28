#pragma once
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include <Ws2tcpip.h>
#include <iostream>
#include "WSAInitializer.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
class IRequestHandler;

class Communicator {
private:
    SOCKET m_serverSocket;
    std::map<SOCKET, IRequestHandler*> m_clients;
    void bindAndListen(const std::string& ip, int port);
    void handleNewClient(SOCKET socket);
    RequestHandlerFactory& m_handlerFactory;
public:
    void startHandleRequests(std::string ip, int port);
    Communicator(RequestHandlerFactory& factory);
    ~Communicator();
};
