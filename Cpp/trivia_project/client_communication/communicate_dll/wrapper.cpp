#include "wrapper.h"


//exporting the functions 
extern "C" LIBRARY_EXPORT void serializeLogin(LoginRequest& req)
{
	jsonSerializer::serializeLogin(req);
}
extern "C" LIBRARY_EXPORT void serializeSignUp(SignUpRequest & req)
{
	jsonSerializer::serializeSignUp(req);
}
extern "C" LIBRARY_EXPORT void serializeSignOut(SignOutRequest & req)
{
	jsonSerializer::serializeSignOut(req);
}
extern "C" LIBRARY_EXPORT void serializeStatus(PlayerStatusRequest& req)
{
	jsonSerializer::serializeStatus(req);
}
extern "C" LIBRARY_EXPORT void serializeExit(ExitRequest & req)
{
	jsonSerializer::serializeExit(req);
}
extern "C" LIBRARY_EXPORT void serializeTopPlayers(TopPlayerRequest & req)
{
	jsonSerializer::serializeTopPlayers(req);
}
extern "C" LIBRARY_EXPORT void serializeListRoom()
{
	jsonSerializer::serializeListRoom();
}
extern "C" LIBRARY_EXPORT void serializeCreateRoom(CreateRoomRequest & req)
{
	jsonSerializer::serializeCreateRoom(req);
}
extern "C" LIBRARY_EXPORT void serializeLeaveRoom(LeaveRoomRequest & req)
{
	jsonSerializer::serializeLeaveRoom(req);
}
extern "C" LIBRARY_EXPORT void serializeJoinRoom(JoinRoomRequest & req)
{
	jsonSerializer::serializeJoinRoom(req);
}
extern "C" LIBRARY_EXPORT void serializeListUsers(ListUserRequest & req)
{
	jsonSerializer::serializeListUsers(req);
}



extern "C" LIBRARY_EXPORT LoginResponse deserializeLogin()
{
	return jsonDeserializer::deserializeLogin();
}
extern "C" LIBRARY_EXPORT SignUpResponse deserializeSignUp()
{
	return jsonDeserializer::deserializeSignUp();
}
extern "C" LIBRARY_EXPORT PlayerResultsResponse deserializePlayreStatusRequest()
{
	return jsonDeserializer::deserializePlayreStatusRequest();
}
extern "C" LIBRARY_EXPORT TopPlayersResponse deserializeTopPlayersRequest()
{
	return jsonDeserializer::deserializeTopPlayersRequest();
}
extern "C" LIBRARY_EXPORT listRoomsResponse deserializelistRoomsRequest()
{
	return jsonDeserializer::deserializelistRoomsRequest();
}
extern "C" LIBRARY_EXPORT JoinRoomResponse deserializeJoinRoomResponse()
{
	return jsonDeserializer::deserializeJoinRoomResponse();
}
extern "C" LIBRARY_EXPORT usersInRoomResponse deserializeUserInRoom()
{
	return jsonDeserializer::deserializeUserInRoom();
}