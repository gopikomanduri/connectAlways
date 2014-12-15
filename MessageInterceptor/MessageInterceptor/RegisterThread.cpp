#include "RegisterThread.h"

void RegisterThread::run()
{
	Json::Value root;
	if(registerQueue.empty()!=false)
	{
		root = registerQueue.front();
		std::string Msgevent = root["event"].asString();
		if(Msgevent.compare("register") == true)
		{
			
		}
	}
}