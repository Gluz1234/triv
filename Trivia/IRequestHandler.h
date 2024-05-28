#pragma once
#include "request.h"

class RequestResult;
class RequestInfo;
class IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequest(RequestInfo info) = 0;
	virtual RequestResult RequestHandler(RequestInfo info) = 0;
};