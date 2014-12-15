#ifndef _MESSAGEPARSER
#define _MESSAGEPARSER
#include "..\\jsoncpp-master\\jsoncpp-master\\include\\json\\json.h"
#include "..\\..\\core interfaces\\IMsgParser.h"
#include "..\\..\\core interfaces\\NonDerivable.h"

class JsonMsgParser : public IMsgParser , public NonDerivable
{
	Json::Reader reader;
	Json::Value root;
	bool parsingSuccessful;
	std::string readInputTestFile(const char* path);

public:
	virtual Json::Value parseData(std::string str);
	virtual Json::Value parseData(std::string str , bool isPath);
};
#endif