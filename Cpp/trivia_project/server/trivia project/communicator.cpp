#include "communicator.h"
#include "Responses.h"
#include "Requests.h"
#include "Json.hpp"
#include <iterator>

using json = nlohmann::json;
using std::pair;



communicator::communicator()
{
	//initialize the winsock
	WSADATA wsa_data = {};
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		throw std::exception("WSAStartup Failed");
	//create socket
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

communicator::~communicator()
{
	try
	{
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

										// again stepping out to the global namespace
										// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		handleRequests();
	}
}
/*
	the function accepts new clients and creates new thread for continue treating
*/
void communicator::handleRequests()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::thread t(&communicator::startThreadForNewClient, this, client_socket);
	t.detach();
	handleRequests();
}

/*
	the function called in thread and treat the whole states of client by calling to other functions.
*/
void communicator::startThreadForNewClient(SOCKET clientSocket)
{
	if (checkLogin(clientSocket))
	{
		manuManager(clientSocket);
	}
	closesocket(clientSocket);
}

/*
	functions treats the first user request(first state) of sign in/up or exit.
	the functions also gets the request from the socket
*/

bool communicator::checkLogin(SOCKET clientSocket)
{
	int type = 0, exit = 1;
	try
	{
		while (exit)
		{
			type = _inf.getMessageTypeCode(clientSocket);
			switch (type)
			{
			case LOGIN:
			{
				//treat login request
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				LoginRequest logIn = JsonRequestPacketDeserializer::deserializeLoginRequest(m);
				LoginResponse res;
				if (_db.checkLogin(logIn._username, logIn._password) && std::find(ConnectedUsers.begin(), ConnectedUsers.end(), logIn._username) == ConnectedUsers.end())
				//if user is not already connected
				{
					ConnectedUsers.insert(ConnectedUsers.begin(), logIn._username);
					res._status = _db.getUserId(logIn._username);
					_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(res));
					return true;
				}
				else
				{
					res._status = 0;
					_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(res));
				}
				break;
			}
			case SIGNUP:
			{
				//treats signup
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				SignupRequest signIn = JsonRequestPacketDeserializer::deserializeSignupRequest(m);
				SignupResponse res;
				if (_db.regist(signIn._username, signIn._password))
				{
					ConnectedUsers.insert(ConnectedUsers.begin(), signIn._username);
					res._status = _db.getUserId(signIn._username);
					_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(res));
					return true;
				}
				else
				{
					res._status = 0;
					_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(res));
				}
				break;
			}
			case EXIT:
			{
				//exiting the client
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				ExitRequest out = JsonRequestPacketDeserializer::deserializeExitRequest(m);
				return false;
			}
			default:
				exit = 0;
			}

		}
	}
	catch (const std::exception& e){}
	return false;
}
/*
	the other states treating - the main menu various requests
*/
bool communicator::manuManager(SOCKET clientSocket)
{
	int type = 0, exit = 1;
	try
	{
		while (exit)
		{
			type = _inf.getMessageTypeCode(clientSocket);
			switch (type)
			{
			case SIGNOUT:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				SignoutRequest signout = JsonRequestPacketDeserializer::deserializeSignoutRequest(m);
				ConnectedUsers.erase(std::find(ConnectedUsers.begin(), ConnectedUsers.end(), signout._username));
				startThreadForNewClient(clientSocket);
				return true;
			}
			case PLAYERSTATUS:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				PlayerStatusRequest player = JsonRequestPacketDeserializer::deserializePlayreStatusRequest(m);
				std::list<float> inf = _db.getStatistic(player._name);

				PlayerResults status;
				status.gamesPlayed = (int)inf.front();
				inf.pop_front();
				status.gamesWin = (int)inf.front();
				inf.pop_front();
				status.correctAnswerCount = (int)inf.front();
				inf.pop_front();
				status.wrongAnswerCount = (int)inf.front();
				inf.pop_front();
				status.averageAnswerTime = inf.front();
				inf.pop_front();

				_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(status));
				break;
			}
			case EXIT:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				ExitRequest out = JsonRequestPacketDeserializer::deserializeExitRequest(m);
				ConnectedUsers.erase(std::find(ConnectedUsers.begin(), ConnectedUsers.end(), out._username));
				
				for (auto it = _rooms.begin(); it != _rooms.end(); ++it)
				{
					it->second->usersInRoom.erase(std::find(it->second->usersInRoom.begin(), it->second->usersInRoom.end(), out._username));
				}

				return true;
				break;
			}
			case TOPPLAYRE:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				TopPlayerRequest top = JsonRequestPacketDeserializer::deserializeTopPlayerRequest(m);
				std::list<string> players = _db.getTopPlayers(top._username);
				TopPlayersResponse topPlayers;
				topPlayers.place = std::stoi(players.front());
				players.pop_front();
				topPlayers.first = players.front();
				players.pop_front();
				topPlayers.secound = players.front();
				players.pop_front();
				topPlayers.third = players.front();
				players.pop_front();

				_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(topPlayers));
				break;
			}
			case CREATEDROOM:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				CreateRoomRequest create = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(m);
				room *newRoom = new room();
				newRoom->maxPlayers = create.maxUsers;
				newRoom->numAns = create.ansCount;
				newRoom->numQu = create.questionCount;
				newRoom->roomName = create.roomName;
				newRoom->timePerQu = create.answerTimeout;
				newRoom->usersInRoom.insert(newRoom->usersInRoom.begin(), create.adminName);

				_rooms.insert(std::pair<int, room*>(_db.getUserId(create.adminName), newRoom));
				break;
			}
			case LISTROOM:
			{
				vector<listRoomsResponse> roomList;
				for (auto it = _rooms.begin(); it != _rooms.end(); ++it)
				{
					listRoomsResponse resp;
					resp.lvl = it->second->numAns - 1;
					resp.name = it->second->roomName;
					resp.maxNum = it->second->maxPlayers;
					resp.numOfPlayers = it->second->usersInRoom.size();
					resp.id = it->first;
					roomList.insert(roomList.end(), resp);
				}

				_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(roomList));
				break;
			}
			case LEAVEROOM:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				LeaveRoomRequest leave = JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(m);

				if (leave._admin)
				{
					auto it = _rooms.find(leave._roomId);
					it->second->usersInRoom.clear();
					delete it->second;
					_rooms.erase(leave._roomId);
				}
				else if (_rooms.find(leave._roomId) != _rooms.end())
					_rooms[leave._roomId]->usersInRoom.erase(std::find(_rooms[leave._roomId]->usersInRoom.begin(), _rooms[leave._roomId]->usersInRoom.end(), leave._username));
				break;
			}
			case JOINROOM:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				JoinRoomRequest join = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(m);
				JoinRoomResponse resp = JoinRoomResponse();

				room r = *_rooms[join._roomId];
				if (r.maxPlayers > r.usersInRoom.size())
				{
					resp.enter = 1;
					resp.roomName = r.roomName;
					resp.ansCount = r.numAns;
					resp.answerTimeout = r.timePerQu;
					resp.maxUsers = r.maxPlayers;
					resp.questionCount = r.numQu;
					_rooms[join._roomId]->usersInRoom.insert(_rooms[join._roomId]->usersInRoom.begin(), join._username);
				}
				else
				{
					resp.enter = 0;
				}

				_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(resp));
				break;
			}
			case LISTUSERS:
			{
				vector<unsigned char> m = _inf.getStringPartFromSocket(clientSocket, _inf.getIntPartFromSocket(clientSocket, 4));
				ListUserRequest req = JsonRequestPacketDeserializer::deserializeListUserRequest(m);
				usersInRoomResponse resp;
				if (_rooms.find(req._roomId) != _rooms.end())
					for (auto it = _rooms[req._roomId]->usersInRoom.begin(); it != _rooms[req._roomId]->usersInRoom.end(); it++) {
						resp.users.insert(resp.users.begin(), (1, *it));
					}
				_inf.sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(resp));
				break;
			}
			default:
				exit = 0;
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	return false;
}
