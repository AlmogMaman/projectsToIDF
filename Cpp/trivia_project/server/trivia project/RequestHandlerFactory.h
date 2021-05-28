#include <iostream>
#include "LoginRequestHandler.h"
//todo: include the next handlers
class RequestHandlerFactory
{
public:

	LoginRequestHandler createLoginRequestHandler();
	//MenuRequestHandler createMenuRequestHandler();
	//RoomAdminRequestHandler createRoomAdminRequestHandler();
	//RoomMemberRequestHandler createRoomMemberRequestHandler();
	//GameRequestHandler createGameRequestHandler();

private:
	//LoginManager m_loginManager;
	//RoomManager m_roomManager;
	//HighscoreTable m_highScoreTable;
	//GameManager m_gameManager;
};