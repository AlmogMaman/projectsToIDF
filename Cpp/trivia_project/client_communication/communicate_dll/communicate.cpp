#include "communicate.h"
#include "Json.hpp"
#include "Helper.h"
using json = nlohmann::json;
//codes of messages (types)
enum responsesCodes { ERR = 0, LOGIN = 100, SIGNUP = 101, SIGNOUT = 102, LISTUSERS = 105, LISTROOM = 110, JOINROOM = 112, LEAVEROOM = 113, CREATEDROOM = 111, PLAYERSTATUS = 50, TOPPLAYRE = 31, START = 69, QUESTION = 90, ANS = 99, WIN = 1, EXIT = 3 };

communicator c;
/*
	sends buffer to the server
*/
void sendToServer(vector<unsigned char>& buffer)
{
	//send the serialized data ('buffer') to the server
	
	c.sendData(buffer);
}
/*
	converting ineger to 4 bytes char array by the communication protocol - Length - 4 bytes
*/
vector<unsigned char> intToBytes(int len)
{
	vector<unsigned char> arrayOfByte(4);
	for (int i = 0; i < 4; i++)
		arrayOfByte[3 - i] = (len >> (i * 8));
	return arrayOfByte;
}

communicator::communicator()
{
	//initialize the winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start winsock: " << wsResult << std::endl;
		return;
	}
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (_sock == INVALID_SOCKET)
	{
		std::cerr << "can't create socket " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

}
communicator::~communicator()
{
	try
	{
		closesocket(_sock);
	}
	catch (...) {}
}
void communicator::makeConnection()
{
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	string server_ip = "127.0.0.1";
	inet_pton(AF_INET, server_ip.c_str(), &hint.sin_addr);
	int connResult = connect(_sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "cannot connect to the server " << WSAGetLastError() << std::endl;
		closesocket(_sock);
		WSACleanup();
		return;
	}
}

void communicator::sendData(vector<unsigned char> buff)
{
	int sendResult = send(_sock, (char*)&buff[0], buff.size(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cerr<<"error occured can't send"<<std::endl;
	}
}
vector<unsigned char> communicator::getData()
{
	int type = Helper::getMessageTypeCode(_sock);
	vector<unsigned char> m = Helper::getStringPartFromSocket(_sock, Helper::getIntPartFromSocket(_sock, 4));
	return m;
}



void jsonSerializer::serializeLogin(LoginRequest& req)
{
	json j = { {"username", req._username }, {"password", req._password} };
	
	vector<unsigned char> buffer;
	buffer.push_back(LOGIN);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);


	
}
void jsonSerializer::serializeSignUp(SignUpRequest & req)
{
	json j = { { "username", req._username },{ "password", req._password } };

	vector<unsigned char> buffer;
	buffer.push_back(SIGNUP);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeSignOut(SignOutRequest & req)
{
	json j = { { "username", req._username } };

	vector<unsigned char> buffer;
	buffer.push_back(SIGNOUT);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeStatus(PlayerStatusRequest & req)
{
	json j = { { "name", req._name } };

	vector<unsigned char> buffer;
	buffer.push_back(PLAYERSTATUS);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeExit(ExitRequest & req)
{
	json j = { { "username", req._username } };

	vector<unsigned char> buffer;
	buffer.push_back(EXIT);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeTopPlayers(TopPlayerRequest & req)
{
	json j = { { "username", req._username } };

	vector<unsigned char> buffer;
	buffer.push_back(TOPPLAYRE);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeListRoom()
{
	vector<unsigned char> buffer;
	buffer.push_back(LISTROOM);
	sendToServer(buffer);
}

void jsonSerializer::serializeCreateRoom(CreateRoomRequest& req)
{
	json j = { {"adminName", req.adminName}, { "roomName", req.roomName },{"ansCount",req.ansCount},{"answerTimeout",req.answerTimeout},{"maxUsers",req.maxUsers},{"questionCount",req.questionCount} };

	vector<unsigned char> buffer;
	buffer.push_back(CREATEDROOM);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeLeaveRoom(LeaveRoomRequest & req)
{
	json j = { { "username", req._username },{ "id", req._roomId },{ "admin", req._admin } };

	vector<unsigned char> buffer;
	buffer.push_back(LEAVEROOM);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeJoinRoom(JoinRoomRequest & req)
{
	json j = { { "username", req._username },{ "id", req._roomId } };

	vector<unsigned char> buffer;
	buffer.push_back(JOINROOM);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}

void jsonSerializer::serializeListUsers(ListUserRequest& req)
{
	json j = { { "id", req._roomId } };

	vector<unsigned char> buffer;
	buffer.push_back(LISTUSERS);
	vector<unsigned char> data = json::to_bson(j);
	vector<unsigned char> length = intToBytes(data.size());
	buffer.insert(buffer.end(), length.begin(), length.end());
	buffer.insert(buffer.end(), data.begin(), data.end());
	sendToServer(buffer);
}


usersInRoomResponse jsonDeserializer::deserializeUserInRoom()
{
	usersInRoomResponse* head = new usersInRoomResponse();
	usersInRoomResponse* before = head;
	vector<unsigned char> msg = c.getData();
	if (!msg.size())
		return *head;

	json j = json::from_bson(msg);

	if (j["closed"] == 1)
		return *head;

	for (int i = 0; i < j["user"].size(); i++)
	{
		usersInRoomResponse* room = new usersInRoomResponse();
		room->name = c.toChar(j["user"][i]/*["name"]*/);
		room->next = nullptr;
		before->next = room;
		before = before->next;
	}

	return *head;
}


LoginResponse jsonDeserializer::deserializeLogin()
{
	LoginResponse resp;
	json j = json::from_bson(c.getData());

	resp._status = j["status"];
	return resp;
}

SignUpResponse jsonDeserializer::deserializeSignUp()
{
	SignUpResponse resp;
	json j = json::from_bson(c.getData());

	resp._status = j["status"];
	return resp;
}

PlayerResultsResponse jsonDeserializer::deserializePlayreStatusRequest()
{
	PlayerResultsResponse status;
	json j = json::from_bson(c.getData());

	status.gamesPlayed = j["gamesPlayed"];
	status.gamesWin = j["gamesWin"];
	status.correctAnswerCount = j["correctAnswerCount"];
	status.wrongAnswerCount = j["wrongAnswerCount"];
	status.averageAnswerTime = j["averageAnswerTime"];

	return status;
}

TopPlayersResponse jsonDeserializer::deserializeTopPlayersRequest()
{
	TopPlayersResponse top;
	json j = json::from_bson(c.getData());

	top.place = j["id"];
	top.first = c.toChar(j["first"]);
	top.secound = c.toChar(j["secound"]);
	top.third = c.toChar(j["third"]);

	return top;
}

listRoomsResponse jsonDeserializer::deserializelistRoomsRequest()
{
	listRoomsResponse* head = new listRoomsResponse();
	listRoomsResponse* before = head;
	vector<unsigned char> msg = c.getData();
	if (!msg.size())
		return *head;

	json j = json::from_bson(msg);

	for (int i = 0; i < j["room"].size(); i++)
	{
		listRoomsResponse* room = new listRoomsResponse();
		room->name = c.toChar(j["room"][i]["name"]);
		room->lvl = j["room"][i]["lvl"];
		room->maxNum = j["room"][i]["maxNum"];
		room->numOfPlayers = j["room"][i]["numOfPlayers"];
		room->id = j["room"][i]["id"];

		room->next = nullptr;
		before->next = room;
		before = before->next;
	}

	return *head;
}

JoinRoomResponse jsonDeserializer::deserializeJoinRoomResponse()
{
	JoinRoomResponse room;
	json j = json::from_bson(c.getData());

	room.ansCount = j["ansCount"];
	room.answerTimeout = j["answerTimeout"];
	room.enter = j["enter"];
	room.maxUsers = j["maxUsers"];
	room.questionCount = j["questionCount"];
	room.roomName = c.toChar(j["roomName"]);
	return room;
}



char * communicator::toChar(string str)
{
	char * head = (char*)malloc((str.length()+1)*sizeof(char));
	int i;
	for (i = 0; i < str.length(); i++)
	{
		head[i] = str[i];
	}
	head[i] = 0;
	return head;
}







/*
	the main function of the DLL
*/
BOOL APIENTRY DllMain(HANDLE hModule, // Handle to DLL module

	DWORD ul_reason_for_call,
	LPVOID lpReserved) // Reserved
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		c.makeConnection();
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return TRUE;

}