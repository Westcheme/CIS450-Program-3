#pragma once
#include <string>
using namespace std;

class File
{
private:
	File *subFiles;
	string name;
	int fd;
	
public:
	File();
	void setName(string _name);
	void setFD(int _fd);
}*Root;