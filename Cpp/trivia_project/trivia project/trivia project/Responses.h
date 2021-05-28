#include <iostream>
#include <Vector>
#include <map>
using std::vector;
using std::string;
using std::map;
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

typedef struct GetRoomsResponse
{
	unsigned int _status;
	//vector<RoomData> _rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	vector<string> _rooms;
} GetPlayersInRoomResponse;

typedef struct HighscoreResponse
{
	unsigned int _status;
	//vector<Highscore> _highscores; 
} HighscoreResponse;

typedef struct JoinRoomResponse
{
	unsigned int _status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int _status;
} CreateRoomResponse;

typedef struct CloseRoomResponse
{
	unsigned int _status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int _status;
} StartGameResponse;

typedef struct LeaveRoomResponse
{
	unsigned int _status;
} LeaveRoomResponse;

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
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} PlayerResults;
typedef struct GetGameResultsResponse
{
	unsigned int _status;
	vector<PlayerResults> results;
} GetGameResultsResponse;

typedef struct JsonResponsePacketSerializer
{
	static char* serializeResponse(ErrorResponse);
	static char* serializeResponse(LoginResponse);
	static char* serializeResponse(SignupResponse);
} JsonResponsePacketSerializer;