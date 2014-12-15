#include "stdafx.h"
#ifndef _CACHE_LIB
#define _CACHE_LIB
#include<stdio.h>
#include "..\\..\\core interfaces\\NonDerivable.h"
#include "poco/LRUCache.h"

//template <class tKey>
//class singleKeycacheLib
//{
//static std::map<tKey,userProfileTemplate> existingObjects;
//};
template <class tKey , class userProfileTemplate>
class cacheLib :  public NonDerivable
{
	static std::map<tKey,std::pair<userProfileTemplate,&cacheLib>> existingObjects;
private:
	cacheLib()
	{
		
	}
	
public:
	cacheLib& static getInstance(int count);
	
};
#endif


