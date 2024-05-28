#include "LoginRequestHandler.h"
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) :
	IRequestHandler(), m_handlerFactory(factory), m_loginManager(factory.getLoginManager())
{	
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequest(RequestInfo info)
{
	return info.id == RequestId::MT_LOGIN_REQUEST || info.id == RequestId::MT_SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::RequestHandler(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	if (!isRequest(info))
	{
		ErrorResponse errorRes;
		errorRes.message = "Signup or Login to continue";
		buffer = JsonResponsePacketSerializer::serializeErrorResponse(errorRes);
		RequestResult RequestRes = { buffer, newHandler };
		return RequestRes;
	}

	try
	{
		if (info.id == RequestId::MT_LOGIN_REQUEST)
		{
			LoginRequest userInfo = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
			std::cout << "username: " << userInfo.username << ", password: " << userInfo.password << std::endl;
			LoginResponse logRes;
			logRes.status = RequestId::MT_RESPONSE_OK;
			buffer = JsonResponsePacketSerializer::serializeLoginResponse(logRes);
			std::cout << "Login Successful" << std::endl;
		}
		else
		{
			SignupRequest userInfo = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
			std::cout << "username: " << userInfo.username << ", password: " << userInfo.password << ", email: " << userInfo.email << std::endl;
			SignupResponse signRes;
			signRes.status = RequestId::MT_RESPONSE_OK;
			buffer = JsonResponsePacketSerializer::serializeSignUpResponse(signRes);
			std::cout << "Signup Successful" << std::endl;
		}
	}
	catch (std::exception& e)
	{
		ErrorResponse errorRes;
		errorRes.message = e.what();
		buffer = JsonResponsePacketSerializer::serializeErrorResponse(errorRes);
	}

	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
