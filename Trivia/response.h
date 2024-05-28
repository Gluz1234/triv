#pragma once
#include <string>
#include "Room.h"
#include <vector>
typedef struct ErrorResponse {
    std::string message;
} ErrorResponse;

typedef struct LoginResponse {
    unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
    unsigned int status;
} SignupResponse;

typedef struct LogoutResponse {
    unsigned int status;
} LogoutResponse;

typedef struct CreateRoomResponse {
    unsigned int status;
} CreateRoomResponse;

typedef struct GetRoomResponse {
    unsigned int status;
    std::vector<RoomData> rooms;
} GetRoomResponse;

typedef struct GetPlayersInRoomResponse {
    std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct JoinRoomResponse {
    unsigned int status;
} JoinRoomResponse;

typedef struct getHighScoreResponse {
    unsigned int status;
    std::vector<std::string> statistics;
} getHighScoreResponse;

typedef struct getPersonalStatsResponse {
    unsigned int status;
    std::vector<std::string> statistics;
} getPersonalStatsResponse;

typedef struct GetStatisticsResponse {
    unsigned int status;
    std::vector<std::string> stats;
} GetStatisticsResponse;