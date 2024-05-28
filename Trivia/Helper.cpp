#include "Helper.h"
#define REQ_LEN 1
#define INFO_LEN 4
RequestInfo Helper::getUserRequestInfo(SOCKET sock)
{
	int requestId = getRequestId(sock);
	int bufferLen = getIntPartFromSocket(sock, INFO_LEN);
	std::time_t currTime = std::time(nullptr);
	std::vector<unsigned char> buffer = getBufferFromSocket(sock, bufferLen);
	RequestInfo info = { requestId, currTime, buffer };
	return info;
}

void Helper::sendData(SOCKET sock, std::vector<unsigned char> message)
{
	unsigned char* data = message.data();

	if (send(sock, (const char*)data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

int Helper::getRequestId(SOCKET sock)
{
	char* s = getPartFromSocket(sock, REQ_LEN,0);
	std::string msg(s);

	if (msg == "")
		return 0;

	int res = std::atoi(s);
	delete s;
	return  res;
}

int Helper::getIntPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	return atoi(s);
}

std::vector<unsigned char> Helper::getBufferFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	std::vector<unsigned char> res;
	for (int i = 0; i < bytesNum; i++)
	{
		res.push_back(s[i]);
	}
	return res;
}

std::string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Failed to get info from this socket:";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}
