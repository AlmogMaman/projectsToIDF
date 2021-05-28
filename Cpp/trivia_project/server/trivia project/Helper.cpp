#include "Helper.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(SOCKET sc)
{
	char* s = getPartFromSocket(sc, 1);

	int res = (int)s[0];
	delete s;
	return  res;// < 0 ? res + 128 : res;
}



// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(SOCKET sc, int bytesNum)
{
	unsigned char* s = (unsigned char*)getPartFromSocket(sc, bytesNum, 0);
	int num = (int)s[3];
	for (int i = 1; i < 4; i++)
		num += (int)s[3 - i] * pow(256,i);
	return num;
}

// recieve data from socket according byteSize
// returns the data as string
std::vector <unsigned char> Helper::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	//string res(s);
	std::vector <unsigned char> res;
	for (int i = 0; i< bytesNum; i++)
		res.insert(res.end(), (unsigned char)s[i]);
	return res;
}



// return string after padding zeros if necessary
string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

// recieve data from socket according byteSize
// this is private function
char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

// send data to socket
// this is private function
void Helper::sendData(SOCKET sc, std::vector<unsigned char> message)
{

	if (send(sc, (char*)&message[0], message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}


// send 204 message to specific client
void Helper::sendUpdateMessageToClient(SOCKET sc, string fileContent, string currUser, string nextUser, int position)
{
	string res;

	string code = std::to_string(MT_SERVER_UPDATE);
	string currFileSize = getPaddedNumber(fileContent.size(), 5);
	string currUserSize = getPaddedNumber(currUser.size(), 2);
	string nextUserSize = getPaddedNumber(nextUser.size(), 2);

	res = code + currFileSize + fileContent + currUserSize + currUser + nextUserSize + nextUser + std::to_string(position);

	TRACE("Send update message to celint: %d, currUser=%s, nextUser=%s, position=%d", sc, currUser.c_str(), nextUser.c_str(), position);


}