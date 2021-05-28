#pragma once
#include <iostream>
#include "communicator.h"
#include "RequestHandlerFactory.h"
class Server
{
public:
	void run();
private:
	//IDatabase m_database;
	communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
};