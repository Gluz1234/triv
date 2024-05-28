#pragma once
#include "IRequestHandler.h"
#include "Helper.h"
#include "request.h"
#include "response.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& Factory);
	~LoginRequestHandler();
	virtual bool isRequest(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};