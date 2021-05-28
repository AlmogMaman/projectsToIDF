#include "Responses.h"
#include "Json.hpp"
using json = nlohmann::json;


vector<unsigned char> intToBytes(int len)
{
	vector<unsigned char> arrayOfByte(4);
	for (int i = 0; i < 4; i++)
		arrayOfByte[3 - i] = (len >> (i * 8));
	return arrayOfByte;
}
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	json j = { {"message",err._message} };

	vector<unsigned char> buffer;
	buffer.push_back(ERR);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse resp)
{
	json j = { {"status", resp._status} };
	vector<unsigned char> buffer;
	buffer.push_back(LOGIN);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse resp)
{
	json j = { { "status", resp._status } };
	vector<unsigned char> buffer;
	buffer.push_back(SIGNUP);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(TopPlayersResponse resp)
{
	json j = { { "id", resp.place }, { "first", resp.first }, { "secound", resp.secound }, { "third", resp.third } };
	vector<unsigned char> buffer;
	buffer.push_back(TOPPLAYRE);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(PlayerResults resp)
{
	json j = { { "gamesPlayed", resp.gamesPlayed}, { "gamesWin", resp.gamesWin} , { "correctAnswerCount", resp.correctAnswerCount}, { "wrongAnswerCount", resp.wrongAnswerCount}, { "averageAnswerTime", resp.averageAnswerTime} };
	vector<unsigned char> buffer;
	buffer.push_back(SIGNUP);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(std::vector<listRoomsResponse> resp)
{
	json j;
	int i = 0;
	for (auto it = resp.begin(); it != resp.end(); it++, i++) {
		j["room"][i] = { { "name", it->name}, { "numOfPlayers", it->numOfPlayers }, { "maxNum", it->maxNum }, { "lvl", it->lvl } ,{"id",it->id} };
	}
	vector<unsigned char> data;
	vector<unsigned char> buffer;
	buffer.push_back(LISTROOM);
	if (j.size())
	{
		data = json::to_bson(j);
	}
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());

	return buffer;
}


vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse resp)
{
	json j = { { "status", resp._status } };
	vector<unsigned char> buffer;
	buffer.push_back(PLAYERSTATUS);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}


vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse resp)
{
	json j = { { "enter", resp.enter}, { "roomName", resp.roomName} , { "ansCount", resp.ansCount}, { "answerTimeout", resp.answerTimeout}, { "maxUsers", resp.maxUsers} , { "questionCount", resp.questionCount}};
	vector<unsigned char> buffer;
	buffer.push_back(JOINROOM);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(usersInRoomResponse resp)
{
	json j;
	j["closed"] = resp.users.size() ? 0 : 1;
	int i = 0;
	for (auto it = resp.users.begin(); it != resp.users.end(); it++, i++) {
		j["user"][i] = (1, *it);
	}
	vector<unsigned char> buffer;
	buffer.push_back(LISTUSERS);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	return buffer;
}
