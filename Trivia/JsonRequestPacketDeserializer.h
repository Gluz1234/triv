#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "request.h"
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char>& Buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char>& Buffer);
	static GetPlayersInRoomRequest deserializerGetPlayersRequest(std::vector<unsigned char>& buffer);
	static JoinRoomRequest deserializerJoinRoomRequest(std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializerCreateRoomRequest(std::vector<unsigned char>& buffer);
private:
	static std::string converter(std::vector<unsigned char>& buffer);
};