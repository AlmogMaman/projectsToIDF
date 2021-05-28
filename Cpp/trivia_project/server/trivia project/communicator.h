#pragma once
#include "Helper.h"
#include "SqlManager.h"
#include "Managers.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <map>
#include <string>
#include <iostream>
#include <thread>

#pragma comment(lib, "ws2_32.lib")


using std::map;
using std::string;
#define PORT 54000 //listening port


class communicator
{

public:
	communicator();
	~communicator();

	void bindAndListen();
	void handleRequests();
private:

	bool checkLogin(SOCKET clientSocket);
	bool manuManager(SOCKET clientSocket);

	std::vector<string> ConnectedUsers;
	map<int, room*> _rooms;

	SOCKET _serverSocket;
	Helper _inf;
	DataBase _db;
	//std::vector<room> _rooms;

	//map<SOCKET, IRequestHandler> m_clients;
	//RequestHandlerFactory m_handlerFactory;
	void startThreadForNewClient(SOCKET clientSocket);
};