#include <iostream>
#include <Vector>
#include <map>
using std::vector;
using std::string;
using std::map;
vector<unsigned char> retrieveData(vector<unsigned char>& buff);

typedef struct LoginRequest
{
	string _username;
	string _password;
} LoginRequest;

typedef struct SignupRequest
{
	string _username;
	string _password;
	//string _email = "ani@admin.lo";
} SignupRequest;

typedef struct SignoutRequest
{
	string _username;
} SignoutRequest;

typedef struct ExitRequest
{
	string _username;
} ExitRequest;

typedef struct LeaveRoomRequest
{
	string _username;
	int _roomId;
	int _admin;
} LeaveRoomRequest;

typedef struct JoinRoomRequest
{
	string _username;
	int _roomId;
} JoinRoomRequest;

typedef struct ListUserRequest
{
	unsigned int _roomId;
} ListUserRequest;

typedef struct PlayerStatusRequest
{
	string _name;
} PlayerStatusRequest;

typedef struct TopPlayerRequest
{
	string _username;
} TopPlayerRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int _roomid;
} GetPlayersInRoomRequest;


typedef struct CreateRoomRequest
{
	string adminName;
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int ansCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerId;
} SubmitAnswerRequest;



typedef struct JsonRequestPacketDeserializer
{

	static LoginRequest deserializeLoginRequest(vector<unsigned char> buff);
	static SignupRequest deserializeSignupRequest(vector<unsigned char> buff);
	static SignoutRequest deserializeSignoutRequest(vector<unsigned char> buff);

	static TopPlayerRequest deserializeTopPlayerRequest(vector<unsigned char> buff);

	static ExitRequest deserializeExitRequest(vector<unsigned char> buff);
	static PlayerStatusRequest deserializePlayreStatusRequest(vector<unsigned char> buff);

	static CreateRoomRequest deserializeCreateRoomRequest(vector<unsigned char> buff);

	static JoinRoomRequest deserializeJoinRoomRequest(vector<unsigned char> buff);
	static LeaveRoomRequest deserializeLeaveRoomRequest(vector<unsigned char> buff);

	static ListUserRequest deserializeListUserRequest(vector<unsigned char> buff);

}JsonRequestPacketDeserializer;