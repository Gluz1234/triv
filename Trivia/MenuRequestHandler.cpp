#include "MenuRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "response.h"
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& Factory, LoggedUser& user) :
	IRequestHandler(), m_handlerFactory(Factory), m_roomManager(Factory.getRoomManager()), m_statisticsManager(Factory.getStatisticsManager()), m_user(user)
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequest(RequestInfo info)
{
	return info.id == RequestId::MT_SIGNOUT_REQUEST || info.id == RequestId::MT_GET_ROOMS_REQUEST || info.id == RequestId::MT_GET_PLAYERS_IN_ROOM_REQUEST || info.id == RequestId::MT_GET_HIGH_SCORE || info.id == RequestId::MT_JOIN_ROOM || info.id == RequestId::MT_CREATE_ROOM;
}
RequestResult MenuRequestHandler::RequestHandler(RequestInfo info)
{
	if (!isRequest(info))
	{
		std::string message = "Signup or Login before continue";
		return error(message);
	}

	try
	{
		switch (info.id)
		{
		case RequestId::MT_SIGNOUT_REQUEST:
			return signout(info);
		case RequestId::MT_GET_ROOMS_REQUEST:
			return getRooms(info);
		case RequestId::MT_GET_PLAYERS_IN_ROOM_REQUEST:
			return getPlayersInRoom(info);
		case RequestId::MT_GET_HIGH_SCORE:
			return getHighScore(info);
		case RequestId::MT_JOIN_ROOM:
			return joinRoom(info);
		case RequestId::MT_CREATE_ROOM:
			return createRoom(info);
		}
	}
	catch (nlohmann::json::parse_error& e)
	{
		std::string message = "Invalid Json";
		return error(message);
	}
	catch (const std::exception& e)
	{
		std::string message = e.what();
		std::cout << message << std::endl;
		return error(message);
	}
}




RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	LoginManager loginManager = m_handlerFactory.getLoginManager();
	loginManager.logout(m_user.getUsername());
	std::cout << "Logout Successful" << std::endl;
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<RoomData> rooms = m_roomManager.getRooms();
	std::cout << "Got Rooms" << std::endl;
	GetRoomResponse roomsRes = { RequestId::MT_RESPONSE_OK, rooms };
	buffer = JsonResponsePacketSerializer::serializeGetRoomResponse(roomsRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	GetPlayersInRoomRequest getPlayersReq = JsonRequestPacketDeserializer::deserializerGetPlayersRequest(info.buffer);
	std::cout << "Room ID: " << getPlayersReq.roomID << std::endl;
	Room room = m_roomManager.getRoom(getPlayersReq.roomID);
	std::vector<std::string> players = room.getAllUsers();
	GetPlayersInRoomResponse playersRes = { players };
	buffer = JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(playersRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}


RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<std::string> stats = m_statisticsManager.getUserStatistics(m_user.getUsername());
	getPersonalStatsResponse statsRes = { RequestId::MT_RESPONSE_OK, stats };
	buffer = JsonResponsePacketSerializer::serializePersonalStatsResponse(statsRes);
	std::cout << "statistics for " << m_user.getUsername() << std::endl;
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<std::string> highScores = m_statisticsManager.getHighScore();
	getHighScoreResponse highScoreRes = { RequestId::MT_RESPONSE_OK, highScores };
	buffer = JsonResponsePacketSerializer::serializeHighScoreResponse(highScoreRes);
	std::cout << "high score for " << m_user.getUsername() << std::endl;
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}


RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	JoinRoomRequest joinRoomReq = JsonRequestPacketDeserializer::deserializerJoinRoomRequest(info.buffer);
	std::cout << "Room ID: " << joinRoomReq.roomID << std::endl;
	Room room = m_roomManager.getRoom(joinRoomReq.roomID);
	room.addUser(m_user);
	std::cout << "Room ID: " << joinRoomReq.roomID << std::endl;
	JoinRoomResponse joinRes = { RequestId::MT_RESPONSE_OK };
	buffer = JsonResponsePacketSerializer::serializeJoinRoomResponse(joinRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}



RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	CreateRoomRequest createRoomReq = JsonRequestPacketDeserializer::deserializerCreateRoomRequest(info.buffer);
	int roomID = generateRoomID(createRoomReq.roomName);
	RoomData metadata = { roomID, createRoomReq.roomName, createRoomReq.maxUsers, createRoomReq.questionCount, createRoomReq.answerTimeOut, false };
	m_roomManager.createRoom(m_user, metadata);
	std::cout << m_user.getUsername() << "Has created Room " << roomID << std::endl;
	CreateRoomResponse createRoomRes = { RequestId::MT_RESPONSE_OK };
	buffer = JsonResponsePacketSerializer::serializeCreateRoomResponse(createRoomRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

int MenuRequestHandler::generateRoomID(std::string roomName)
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	int timeFormula = localtm->tm_min + localtm->tm_hour;
	int len = roomName.length();
	return (timeFormula * len) / 1.5;
}

RequestResult MenuRequestHandler::error(const std::string& message)
{
	ErrorResponse errorRes;
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	errorRes.message = message;
	buffer = JsonResponsePacketSerializer::serializeErrorResponse(errorRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}