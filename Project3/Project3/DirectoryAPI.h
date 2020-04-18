#pragma once
#include "UMDLibOS.h"
#include "INode.h"
#include <iostream>
using namespace std;

class DirectoryAPI
{
private:
	int numDirectories;
	bool INodeBitmap[NUM_SECTORS];
public:
	DirectoryAPI();
	int Dir_Create(string path);
	int Dir_Size(string path);
	int Dir_Read(string path, string buffer, int size);
	int Dir_Unlink(string path);
	INode* findDirectory(string path);
	int getNumDirectories();
};

