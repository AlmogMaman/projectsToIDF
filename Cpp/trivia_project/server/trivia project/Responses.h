#pragma once
#include <iostream>
#include <Vector>
#include <map>
using std::vector;
using std::string;
using std::map;

enum responsesCodes { ERR = 0, LOGIN = 100, SIGNUP = 101, SIGNOUT = 102, LISTUSERS = 105, LISTROOM = 110, JOINROOM = 112, LEAVEROOM = 113, CREATEDROOM = 111, PLAYERSTATUS = 50, TOPPLAYRE = 31, START = 69, QUESTION = 90, ANS = 99, WIN = 1, EXIT = 3 };


typedef struct ErrorResponse
{
	string _message;
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int _status;
}LoginResponse;

typedef struct SignupResponse
{
	unsigned int _status;
} SignupResponse;

typedef struct LogoutResponse
{
	unsigned int _status;
} LogoutResponse;

typedef struct GetRoomStateResponse
{
	unsigned int _status;
	bool _hasGameBegun;
	vector<string> _players;
	unsigned int questionCount;
	bool _answerTimeout;
} GetRoomStateResponse;

typedef struct GetQuestionResponse
{
	unsigned int _status;
	string question;
	map<unsigned int, string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	unsigned int _status;
	unsigned int correctAnswerId;
} SubmitAnswerResponse;

typedef struct PlayerResults
{
	unsigned int gamesPlayed;
	unsigned int gamesWin;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
} PlayerResults;

typedef struct TopPlayersResponse
{
	unsigned int place;
	string first;
	string secound;
	string third;
} TopPlayersResponse;

typedef struct listRoomsResponse
{
	string name;
	unsigned int numOfPlayers;
	unsigned int maxNum;
	unsigned int lvl;
	unsigned int id;
} listRoomsResponse;

typedef struct JoinRoomResponse
{
	unsigned int enter;
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int ansCount;
	unsigned int answerTimeout;
} JoinRoomResponse;

typedef struct usersInRoomResponse
{
	std::vector<string> users;
}usersInRoomResponse;

//typedef struct GetGameResultsResponse
//{
//	unsigned int _status;
//	vector<PlayerResults> results;
//} GetGameResultsResponse;
//
//typedef struct GetRoomsResponse
//{
//	unsigned int _status;
//	//vector<RoomData> _rooms;
//} GetRoomsResponse;
//
//typedef struct GetPlayersInRoomResponse
//{
//	vector<string> _rooms;
//} GetPlayersInRoomResponse;
//
//typedef struct HighscoreResponse
//{
//	unsigned int _status;
//	//vector<Highscore> _highscores; 
//} HighscoreResponse;
//
//typedef struct CreateRoomResponse
//{
//	unsigned int _status;
//} CreateRoomResponse;
//
//typedef struct CloseRoomResponse
//{
//	unsigned int _status;
//} CloseRoomResponse;
//
//typedef struct StartGameResponse
//{
//	unsigned int _status;
//} StartGameResponse;
//
//typedef struct LeaveRoomResponse
//{
//	unsigned int _status;
//} LeaveRoomResponse;

vector<unsigned char> intToBytes(int len);

typedef struct JsonResponsePacketSerializer
{
	static vector<unsigned char> serializeResponse(ErrorResponse);
	static vector<unsigned char> serializeResponse(LogoutResponse);
	static vector<unsigned char> serializeResponse(LoginResponse);
	static vector<unsigned char> serializeResponse(SignupResponse);
	static vector<unsigned char> serializeResponse(TopPlayersResponse);
	static vector<unsigned char> serializeResponse(PlayerResults);
	static vector<unsigned char> serializeResponse(std::vector<listRoomsResponse>);
	static vector<unsigned char> serializeResponse(JoinRoomResponse);
	static vector<unsigned char> serializeResponse(usersInRoomResponse);


} JsonResponsePacketSerializer;