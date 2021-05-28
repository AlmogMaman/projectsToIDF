#include "Requests.h"
#include "json.hpp"
using json = nlohmann::json;
vector<unsigned char> retrieveData(vector<unsigned char>& buff)
{
	int i = 0;
	auto it = buff.begin();
	for (it = buff.begin(); it != buff.end() && i < 5; it++, i++); // 5 - the first char of the data
	vector<unsigned char> data(it, buff.end());
	return data;
}

/*
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<unsigned char> buff)
{
	LoginRequest ansStruct;
	//vector<unsigned char> data = retrieveData(buff);
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	ansStruct._password = j["password"];
	return ansStruct;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<unsigned char> buff)
{
	SignupRequest ansStruct;
	//vector<unsigned char> data = retrieveData(buff);
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	ansStruct._password = j["password"];
	//ansStruct._email = j["email"];
	return ansStruct;
}

SignoutRequest JsonRequestPacketDeserializer::deserializeSignoutRequest(vector<unsigned char> buff)
{
	SignoutRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	return ansStruct;
}

TopPlayerRequest JsonRequestPacketDeserializer::deserializeTopPlayerRequest(vector<unsigned char> buff)
{
	TopPlayerRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	return ansStruct;
}

ExitRequest JsonRequestPacketDeserializer::deserializeExitRequest(vector<unsigned char> buff)
{
	ExitRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	return ansStruct;
}

PlayerStatusRequest JsonRequestPacketDeserializer::deserializePlayreStatusRequest(vector<unsigned char> buff)
{
	PlayerStatusRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._name = j["name"];
	return ansStruct;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(vector<unsigned char> buff)
{
	CreateRoomRequest room;
	json j = json::from_bson(buff);
	room.adminName = j["adminName"];
	room.roomName = j["roomName"];
	room.ansCount = j["ansCount"] + 1;
	room.answerTimeout = j["answerTimeout"];
	room.maxUsers = j["maxUsers"];
	room.questionCount = j["questionCount"];
	return room;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(vector<unsigned char> buff)
{
	JoinRoomRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	ansStruct._roomId = j["id"];
	return ansStruct;
}

LeaveRoomRequest JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(vector<unsigned char> buff)
{
	LeaveRoomRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._username = j["username"];
	ansStruct._roomId = j["id"];
	ansStruct._admin = j["admin"];
	return ansStruct;
}

ListUserRequest JsonRequestPacketDeserializer::deserializeListUserRequest(vector<unsigned char> buff)
{
	ListUserRequest ansStruct;
	json j = json::from_bson(buff);
	ansStruct._roomId = j["id"];
	return ansStruct;
}
