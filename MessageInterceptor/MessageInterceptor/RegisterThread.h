#ifndef _REGISTERTHREAD
#define _REGISTERTHREAD
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "..\\jsoncpp-master\\jsoncpp-master\\include\\json\\json.h"
#include "declarations.h"
#include "..\\..\\core interfaces\\NonDerivable.h"
#include "../MessageParser/MessageParser.h"
#include<iostream>

extern std::queue<Json::Value > registerQueue;

class RegisterThread : public Poco::Runnable , NonDerivable
{

	virtual void run();
	
};



#endif