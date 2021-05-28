#pragma once
#define LIBRARY_EXPORT __declspec(dllexport)
#include <iostream>
#include <vector>
#include "communicate.h"
using std::string;
#define EXPORT extern "C" __declspec(dllexport)

extern "C" LIBRARY_EXPORT void serializeLogin(LoginRequest& req);
extern "C" LIBRARY_EXPORT void serializeSignUp(SignUpRequest & req);
extern "C" LIBRARY_EXPORT void serializeSignOut(SignOutRequest & req);
extern "C" LIBRARY_EXPORT void serializeStatus(PlayerStatusRequest & req);
extern "C" LIBRARY_EXPORT void serializeExit(ExitRequest & req);
extern "C" LIBRARY_EXPORT void serializeTopPlayers(TopPlayerRequest & req);
extern "C" LIBRARY_EXPORT void serializeListRoom();
extern "C" LIBRARY_EXPORT void serializeCreateRoom(CreateRoomRequest & req);
extern "C" LIBRARY_EXPORT void serializeLeaveRoom(LeaveRoomRequest & req);
extern "C" LIBRARY_EXPORT void serializeJoinRoom(JoinRoomRequest & req);
extern "C" LIBRARY_EXPORT void serializeListUsers(ListUserRequest & req);


extern "C" LIBRARY_EXPORT LoginResponse deserializeLogin();
extern "C" LIBRARY_EXPORT SignUpResponse deserializeSignUp();
extern "C" LIBRARY_EXPORT PlayerResultsResponse deserializePlayreStatusRequest();
extern "C" LIBRARY_EXPORT TopPlayersResponse deserializeTopPlayersRequest();
extern "C" LIBRARY_EXPORT listRoomsResponse deserializelistRoomsRequest();
extern "C" LIBRARY_EXPORT JoinRoomResponse deserializeJoinRoomResponse();
extern "C" LIBRARY_EXPORT usersInRoomResponse deserializeUserInRoom();