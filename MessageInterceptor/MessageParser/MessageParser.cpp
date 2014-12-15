#include "stdafx.h"
#include "MessageParser.h"
#include<iostream>

Json::Value JsonMsgParser::parseData(std::string str)
{
	Json::Value nullValue = Json::Value(0);
	if (false == (parsingSuccessful = reader.parse (str,root)))
	{
		std::cerr<<"\nFailed to parse configuration:"
			<<reader.getFormatedErrorMessages ();
		return nullValue;
	}
	return root;

	/*Json::Value event = root["event"];
	std::string eventName = event.asString();
	if(eventName.)
	Json::Value wareHouse = stock["warehouse"].asInt();
	int wareH = wareHouse.asInt(); 
	int verbName = root.get ("id","").asInt ();
	Json::Value data = root.get ("tags",0);*/
}



Json::Value JsonMsgParser::parseData(std::string str , bool isPath)
{
	std::string msg = readInputTestFile(str.c_str());
	return parseData(msg);
}

std::string JsonMsgParser::readInputTestFile(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (!file)
		return std::string("");
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	std::string text;
	char* buffer = new char[size + 1];
	buffer[size] = 0;
	if (fread(buffer, 1, size, file) == (unsigned long)size)
		text = buffer;
	fclose(file);
	delete[] buffer;
	return text;
}

