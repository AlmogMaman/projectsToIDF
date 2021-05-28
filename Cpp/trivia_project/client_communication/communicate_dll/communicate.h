#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 54000
using std::vector;
using std::string;



vector<unsigned char> intToBytes(int len);

void sendToServer(vector<unsigned char>& buffer);


//request/response structures
typedef struct LoginRequest
{
	char* _username;
	char* _password;
}LoginRequest;

typedef struct SignUpRequest
{
	char* _username;
	char* _password;
}SignUpRequest;

typedef struct SignOutRequest
{
	char* _username;
}SignOutRequest;

typedef struct CreateRoomRequest
{
	char* adminName;
	char* roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int ansCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct ExitRequest
{
	char* _username;
}ExitRequest;

typedef struct TopPlayerRequest
{
	char* _username;
} TopPlayerRequest;

typedef struct LeaveRoomRequest
{
	char* _username;
	unsigned int _roomId;
	unsigned int _admin;
} LeaveRoomRequest;

typedef struct JoinRoomRequest
{
	char* _username;
	unsigned int _roomId;
} JoinRoomRequest;

typedef struct ListUserRequest
{
	unsigned int _roomId;
} ListUserRequest;

typedef struct LoginResponse
{
	unsigned int _status;
}LoginResponse;

typedef struct SignUpResponse
{
	unsigned int _status;
}SignUpResponse;

typedef struct PlayerStatusRequest
{
	char* _name;
} PlayerStatusRequest;

typedef struct PlayerResultsResponse
{
	unsigned int gamesPlayed;
	unsigned int gamesWin;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
} PlayerResultsResponse;

typedef struct TopPlayersResponse
{
	unsigned int place;
	char* first;
	char* secound;
	char* third;
} TopPlayersResponse;

typedef struct listRoomsResponse
{
	char* name;
	unsigned int numOfPlayers;
	unsigned int maxNum;
	unsigned int lvl;
	unsigned int id;
	listRoomsResponse *next;
} listRoomsResponse;

typedef struct JoinRoomResponse
{
	unsigned int enter;
	char* roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int ansCount;
	unsigned int answerTimeout;
} JoinRoomResponse;

typedef struct usersInRoomResponse
{
	char* name;
	usersInRoomResponse* next;
}usersInRoomResponse;

/*
	the socket handler class - connecting to the server
	assists by the Helper for sending and getting data to/from the serber 
*/
class communicator
{
public:
	
	communicator();
	~communicator();
	void makeConnection();
	void sendData(vector<unsigned char> buff);
	vector<unsigned char> getData();
	char* toChar(string str);
	
private:
	SOCKET _sock;
};

/*
	serializing all requests types(structures) by specific protocol
*/
class jsonSerializer
{
public:
	static void serializeLogin(LoginRequest& req);
	static void serializeSignOut(SignOutRequest& req);
	static void serializeSignUp(SignUpRequest& req);
	static void serializeStatus(PlayerStatusRequest& req);
	static void serializeExit(ExitRequest & req);
	static void serializeTopPlayers(TopPlayerRequest & req);
	static void serializeListRoom();
	static void serializeCreateRoom(CreateRoomRequest & req);

	static void serializeLeaveRoom(LeaveRoomRequest & req);
	static void serializeJoinRoom(JoinRoomRequest & req);

	static void serializeListUsers(ListUserRequest& req);


};
/*
	deserializing all responses types(structures) by specific protocol
*/
class jsonDeserializer
{
public:
	static LoginResponse jsonDeserializer::deserializeLogin();
	static SignUpResponse jsonDeserializer::deserializeSignUp();
	static PlayerResultsResponse jsonDeserializer::deserializePlayreStatusRequest();
	static TopPlayersResponse jsonDeserializer::deserializeTopPlayersRequest();

	static listRoomsResponse jsonDeserializer::deserializelistRoomsRequest();
	static JoinRoomResponse jsonDeserializer::deserializeJoinRoomResponse();

	static usersInRoomResponse jsonDeserializer::deserializeUserInRoom();


	

};
