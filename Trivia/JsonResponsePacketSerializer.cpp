#include "JsonResponsePacketSerializer.h"
#include "json.hpp"



std::vector<uint8_t> JsonResponsePacketSerializer::serializeLoginResponse(const LoginResponse& response) 
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return createBuffer(json_response.dump(), 1);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeSignUpResponse(const SignupResponse& response) 
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return createBuffer(json_response.dump(), 2);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeErrorResponse(const ErrorResponse& response) 
{
    nlohmann::json json_response;
    json_response["message"] = response.message;
    return createBuffer(json_response.dump(), 3);
}
std::vector<uint8_t> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse& response) 
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return createBuffer(json_response.dump(), 3);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse& response) 
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return createBuffer(json_response.dump(), 4);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeGetRoomResponse(const GetRoomResponse& response) 
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    nlohmann::json json_rooms = nlohmann::json::array();
    for (const auto& room : response.rooms) 
    {
        nlohmann::json json_room;
        json_room["id"] = room._RoomId;
        json_room["name"] = room._Name;
        json_room["maxPlayers"] = room._maxPlayers;
        json_room["numOfQuestionsInGame"] = room._numOfQuestionsInGame;
        json_room["timePerQuestion"] = room._TimePerQuestion;
        json_room["isActive"] = room._isActive;
        json_rooms.push_back(json_room);
    }
    json_response["rooms"] = json_rooms;

    return createBuffer(json_response.dump(), 5);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response) 
{
    nlohmann::json json_response;
    json_response["players"] = response.players;
    return createBuffer(json_response.dump(), 6);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse& response) 
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return createBuffer(json_response.dump(), 7);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeHighScoreResponse(const getHighScoreResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    json_response["statistics"] = response.statistics;
    return createBuffer(json_response.dump(), 8);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializePersonalStatsResponse(const getPersonalStatsResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    json_response["statistics"] = response.statistics;
    return createBuffer(json_response.dump(), 8);
}

std::vector<uint8_t> JsonResponsePacketSerializer::createBuffer(const std::string& json_str, uint8_t code) 
{
    std::vector<uint8_t> buffer;
    //alon this is the first 4 bytes of the protocol
    buffer.push_back(code);
    buffer.push_back(json_str.size() >> 24 & 0xFF);
    buffer.push_back(json_str.size() >> 16 & 0xFF);
    buffer.push_back(json_str.size() >> 8 & 0xFF);
    buffer.push_back(json_str.size() & 0xFF);
    for (char c : json_str) 
    {
        buffer.push_back(static_cast<uint8_t>(c));
    }
    return buffer;
}