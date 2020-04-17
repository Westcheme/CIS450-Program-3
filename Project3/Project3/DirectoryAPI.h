#pragma once
#include "UMDLibOS.h"
#include "INode.h"
#include <string>
using namespace std;

class DirectoryAPI
{
private:
	bool INodeBitmap[NUM_SECTORS];
public:
	int Dir_Create(string path);
	int Dir_Size(string path);
	int Dir_Read(string path, string buffer, int size);
	int Dir_Unlink(string path);
};

