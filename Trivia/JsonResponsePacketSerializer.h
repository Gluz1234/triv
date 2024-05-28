#pragma once
#include <vector>
#include <string>
#include "response.h"
#include "json.hpp"
#include <cstdint>
class JsonResponsePacketSerializer
{
public:
    static std::vector<uint8_t> serializeLoginResponse(const LoginResponse& response);
    static std::vector<uint8_t> serializeSignUpResponse(const SignupResponse& response);
    static std::vector<uint8_t> serializeErrorResponse(const ErrorResponse& response);
    static std::vector<uint8_t> serializeLogoutResponse(const LogoutResponse& response);
    static std::vector<uint8_t> serializeCreateRoomResponse(const CreateRoomResponse& response);
    static std::vector<uint8_t> serializeGetRoomResponse(const GetRoomResponse& response);
    static std::vector<uint8_t> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response);
    static std::vector<uint8_t> serializeJoinRoomResponse(const JoinRoomResponse& response);
    static std::vector<uint8_t> serializeHighScoreResponse(const getHighScoreResponse& response);
    static std::vector<uint8_t> serializePersonalStatsResponse(const getPersonalStatsResponse& response);

private:
    static std::vector<uint8_t> createBuffer(const std::string& json_str, uint8_t code);
};