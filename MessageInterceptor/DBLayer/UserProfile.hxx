#ifndef USERPROFILE_HXX
#define USERPROFILE_HXX
#include<string>
#include<odb/core.hxx>
#include<odb/nullable.hxx>
#pragma db object
class UserProfile
{
public:
UserProfile()
{

}
protected:
private:
	friend class odb::access;
//#pragma db null
	std::string _userId;
	odb::nullable<std::string> _userName;
	odb::nullable<std::string> _emailId;
	odb::nullable<unsigned long long> phoneNumber;
#pragma db member(_userId) id

};
#endif