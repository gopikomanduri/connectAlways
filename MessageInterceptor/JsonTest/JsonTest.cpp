#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<fstream>
#include "../jsoncpp-master/jsoncpp-master/include/json/json.h"

using namespace std;

std::string readInputTestFile(const char* path) {
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


int main (){
unsigned int i,j;
char fileName[] ="F:\\gopi\\personal\\MyApsCode\\connectAlways\\MessageInterceptor\\JsonTest\\abc_2.json";
 
ifstream infile;
infile.exceptions (ios::failbit|ios::badbit);
try
{
infile.open (fileName);
}
catch (ifstream::failure& e)
{
cerr<<"\n Exception opening file "<<fileName<<": "<<e.what ();
return 0;
}
 
string input;
Json::Reader reader;
Json::Value root;
bool parsingSuccessful;
 
try
{
	std::string input = readInputTestFile(fileName);
//while (getline (infile,input,'\n'))
{
if (false == (parsingSuccessful = reader.parse (input,root)))
{
cerr<<"\nFailed to parse configuration:"
<<reader.getFormatedErrorMessages ();
return 0;
}
else
{
// Json::Value sample = root["id"];
 Json::Value stock = root["stock"];
 Json::Value wareHouse = stock["warehouse"].asInt();
 int wareH = wareHouse.asInt(); 
int verbName = root.get ("id","").asInt ();
Json::Value data = root.get ("tags",0);
cout << "size is " << data.size() <<endl;
 
//vector<float> freq (mWidth * mHeight);
for (int i = 0; i < data.size(); i++){
int sizeint = data[i].size();
cout <<endl <<"---------------" <<endl;
cout << "Size of individual is " <<sizeint << endl;
Json::Value dat1 = data[i];
 
for(int j=0; j< dat1.size(); j++){
cout << dat1[j].asDouble() << " ,";
}
 
}
}
}
}
catch (ifstream::failure& e)
{
 
}
 
return 0;
}
