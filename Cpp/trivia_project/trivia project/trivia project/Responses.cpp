#include "Responses.h"

char * JsonResponsePacketSerializer::serializeResponse(ErrorResponse)
{
	return nullptr;
}

char * JsonResponsePacketSerializer::serializeResponse(LoginResponse)
{
	return nullptr;
}

char * JsonResponsePacketSerializer::serializeResponse(SignupResponse)
{
	return nullptr;
}
