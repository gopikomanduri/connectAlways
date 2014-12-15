#ifndef FriendDetail_HXX
#define FriendDetail_HXX
#include<string>
#include<odb/core.hxx>
#include<odb/nullable.hxx>
#pragma db object
class contacts
{
public:
	contacts()
	{

	}
private:
	friend class odb::access;
	#pragma db id auto
	unsigned long long contactId;
	std::string _fromUser;
	std::string _toUser;
	int status;
protected:
};
#endif
