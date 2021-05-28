#include <iostream>
#include <Vector>
#include <map>
using std::vector;
using std::string;
using std::map;

typedef struct LoginRequest
{
	string _username;
	string _password;
} LoginRequest;

typedef struct SignupRequest
{
	string _username;
	string _password;
	string _email;
} SignupRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int _roomid;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int _roomid;
} JoinRoomRequest;

typedef struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerId;
} SubmitAnswerRequest;
struct JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(char* buff);
	static SignupRequest deserializeSignupRequest(char* buff);
}JsonRequestPacketDeserializer;