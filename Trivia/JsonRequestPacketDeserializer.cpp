#include "JsonRequestPacketDeserializer.h"
#include "request.h"
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& Buffer)
{
    std::string convStr = converter(Buffer);
    auto magic = nlohmann::json::parse(convStr);
    LoginRequest data = { magic.at("username"),magic.at("password") };
    return data;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char>& Buffer)
{
    std::string convStr = converter(Buffer);
    auto magic = nlohmann::json::parse(convStr);
    SignupRequest data = { magic.at("username"),magic.at("password"),magic.at("mail")};
    return data;
}

std::string JsonRequestPacketDeserializer::converter(std::vector<unsigned char>& buffer)
{
    std::string new_Str = "";
    for (auto i = buffer.begin(); i != buffer.end(); i++)
    {
        new_Str += (char)*i;
    }
    return new_Str;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializerGetPlayersRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = converter(buffer);
    auto j = nlohmann::json::parse(jsonStr);
    unsigned int roomID = j.at("roomID");

    GetPlayersInRoomRequest info = { roomID };
    return info;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializerJoinRoomRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = converter(buffer);
    auto j = nlohmann::json::parse(jsonStr);
    unsigned int roomID = j.at("roomID");

    JoinRoomRequest info = { roomID };
    return info;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializerCreateRoomRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = converter(buffer);
    auto j = nlohmann::json::parse(jsonStr);
    std::string roomName = j.at("roomName");
    unsigned int maxUsers = j.at("maxUsers");
    unsigned int questionCount = j.at("questionCount");
    unsigned int answerTimeout = j.at("answerTimeout");

    CreateRoomRequest info = { roomName, maxUsers, questionCount, answerTimeout };
    return info;
}

