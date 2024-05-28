#pragma once
#include <string>
#include <ctime>
#include <vector>
#include "IRequestHandler.h"
class IRequestHandler;
typedef struct LoginRequest
{
	std::string username;
	std::string password;
}LoginRequest;
typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}SignupRequest;
typedef struct RequestInfo
{
	int id;
	std::time_t recTime;
	std::vector<unsigned char> buffer;
}RequestInfo;
typedef struct RequestResult
{
	std::vector<unsigned char> resBuffer;
	IRequestHandler* newHandler;
}RequestResult;
typedef struct GetPlayersInRoomRequest
{
	unsigned int roomID;

}GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomID;

}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;

}CreateRoomRequest;