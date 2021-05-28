#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <map>
#include <string>
#include <iostream>
#include <thread>
#pragma comment(lib, "ws2_32.lib");

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
	SOCKET _serverSocket;
	//map<SOCKET, IRequestHandler> m_clients;
	//RequestHandlerFactory m_handlerFactory;
	void startThreadForNewClient();
};