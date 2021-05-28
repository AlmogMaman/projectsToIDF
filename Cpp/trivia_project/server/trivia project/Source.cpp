#include "communicator.h"

int main()
{
	//intiallizing communicator and starting to wait for clients
	communicator c;
	c.bindAndListen();
	
	return 0;
}