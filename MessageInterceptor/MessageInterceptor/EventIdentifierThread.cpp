//#include "stdafx.h"
#include "EventIdentifierThread.h"

//EventIdentifierThread::EventIdentifierThread(EventDetails details)
//{
//	_eventDetails = new EventDetails();
//	_eventDetails.emailId.copy(details.emailId,details.emailId.length());
//	_eventDetails.number.copy(details.number,details.number.length());
//	_eventDetails.userName.copy(details.userName,details.number.length());
//	_eventDetails.isRegister = details.isRegister;
//}

void EventIdentifierThread::run()
{
	std::string msg;
	Json::Value root;
	while(rawQueue.empty()!=true)
	{
		msg = rawQueue.front();
		root = msgParser->parseData(msg);
		if(root.isNull() != true)
		{
			std::string Msgevent = root["event"].asString();
			if(Msgevent.compare("register") == true)
			{
				registerQueue.push(root);
			}
			else if(Msgevent.compare("login") == true)
			{
				loginQueue.push(root);
			}
			else if(Msgevent.compare("update") == true)
			{
				updateQueue.push(root);
			}
		}
		
	}
}