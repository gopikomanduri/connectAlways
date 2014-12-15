#include "CachingLib.h"

template <class tKey  , class userProfileTemplate>
cacheLib& static cacheLib::getInstance(int count)
{
	if((existingObjects!= NULL)&&(existingObjects[tKey]!=NULL))
	{
		std::pair<userProfileTemplate,&cacheLib> value = existingObjects[tKey];
		if(value != NULL)
		{
			return value.second;
		}
		else
		{
			new 
		}


	}
}

