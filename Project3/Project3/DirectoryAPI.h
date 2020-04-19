#pragma once
#include "UMDLibOS.h"
using namespace std;

class UMDLibOS;

class DirectoryAPI
{
private:
	int numDirectories;
public:
	DirectoryAPI();
	int Dir_Create(string path);
	int Dir_Size(string path);
	int Dir_Read(string path, string& buffer, int size);
	int Dir_Unlink(string path);
	int getNumDirectories();
	static unique_ptr<DirectoryINode>* findDirectory(string path);
};

