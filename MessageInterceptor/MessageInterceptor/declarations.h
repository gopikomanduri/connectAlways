#ifndef _DECLARATIONS
#define _DECLARATIONS
#include<queue>
extern std::queue<Json::Value > registerQueue;
extern std::queue<Json::Value > updateQueue;
extern std::queue<Json::Value > loginQueue;
extern std::queue<std::string> rawQueue;
typedef struct _EventDetails
{
	std::string userName;
	std::string number;
	std::string emailId;
	bool isRegister;
}EventDetails;

//extern IMsgParser *msgParser;
#endif