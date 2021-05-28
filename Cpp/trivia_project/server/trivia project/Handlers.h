#pragma once 
#include <iostream>
#include <Vector>
#include <map>
#include <ctime>
using std::vector;
using std::string;
using std::map;
typedef struct Request
{
	unsigned int RequestId;
	time_t recivalTime;
	vector<unsigned char> buffer;
}Request;

typedef struct RequestResult
{
	vector<unsigned char> response;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request) = 0;
	virtual RequestResult handleRequest(Request) = 0;
};