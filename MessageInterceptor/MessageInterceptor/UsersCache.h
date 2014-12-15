#ifndef _USER_CACHE
#define _USER_CACHE

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "..\\jsoncpp-master\\jsoncpp-master\\include\\json\\json.h"
#include "declarations.h"
#include "..\\..\\core interfaces\\NonDerivable.h"
#include "../MessageParser/MessageParser.h"
#include<iostream>

class UsersCacheThread : Poco::Runnable, public NonDerivable
{
	EventDetails _eventDetails;
	IMsgParser *msgParser;

public:
	UsersCacheThread()
	{
		
	}
	virtual void run();

};



#endif