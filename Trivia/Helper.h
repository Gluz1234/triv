#pragma once
#include "IRequestHandler.h"
#include "request.h"
#include <string>
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

enum RequestId
{
	MT_LOGIN_REQUEST = 1,
	MT_SIGNUP_REQUEST = 2,
	MT_SIGNOUT_REQUEST = 3,
	MT_GET_ROOMS_REQUEST = 4,
	MT_GET_PLAYERS_IN_ROOM_REQUEST = 5,
	MT_GET_HIGH_SCORE = 6,
	MT_JOIN_ROOM = 7,
	MT_CREATE_ROOM = 8,
	MT_RESPONSE_OK = 0,
	//it used to be 9 if it will be an issue in the future
	MT_EXIT = 99,
	MT_ERROR = 99
};

class Helper
{
public:
	static RequestInfo getUserRequestInfo(SOCKET sock);
	static void sendData(SOCKET sock, std::vector<unsigned char> message);
	static int getRequestId(SOCKET sock);
	static int getIntPartFromSocket(SOCKET sc, int bytesNum);
	static std::vector<unsigned char> getBufferFromSocket(SOCKET sc, int bytesNum);



private:
	static std::string getPaddedNumber(int num, int digits);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
};