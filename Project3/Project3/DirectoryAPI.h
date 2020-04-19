#pragma once
#include "UMDLibOS.h"
using namespace std;

class UMDLibOS;

static int numDirectories;

class DirectoryAPI
{
private:
public:
	DirectoryAPI();
	static int Dir_Create(string path);
	static int Dir_Size(string path);
	static int Dir_Read(string path, string& buffer, int size);
	static int Dir_Unlink(string path);
	static int getNumDirectories();
	static DirectoryINode* findDirectory(string path);
};

