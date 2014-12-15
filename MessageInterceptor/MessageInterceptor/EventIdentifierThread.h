#ifndef _EVENTIDENTIFIER
#define _EVENTIDENTIFIER

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "..\\jsoncpp-master\\jsoncpp-master\\include\\json\\json.h"
#include "declarations.h"
#include "..\\..\\core interfaces\\NonDerivable.h"
#include "../MessageParser/MessageParser.h"
#include<iostream>

std::queue<Json::Value > registerQueue;
std::queue<Json::Value > updateQueue;
std::queue<Json::Value > loginQueue;
extern std::queue<std::string> rawQueue;
extern IMsgParser *msgParser;

class EventIdentifierThread : Poco::Runnable, public NonDerivable
{
	EventDetails _eventDetails;
	IMsgParser *msgParser;

public:
	EventIdentifierThread()
	{
		msgParser = new JsonMsgParser();
	}
	virtual void run();
	
};

#endif