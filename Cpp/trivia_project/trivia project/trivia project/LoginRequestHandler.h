#include "Handlers.h"

class LoginRequestHandler : IRequestHandler
{
private:
	//LoginManager m_loginManager
	//RequestHandlerFactory m_handlerFactory
	RequestResult login(Request);
	RequestResult signup(Request);

public:
	virtual bool isRequestRelevant(Request) override;
	virtual RequestResult handleRequest(Request) override;
};