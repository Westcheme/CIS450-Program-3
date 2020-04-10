#pragma once
#include "INode.h"
#include <string>
using namespace std;

class DirectoryAPI
{
public:
	int Dir_Create(string path);
	int Dir_Size(string path);
	int Dir_Read(string path, string buffer, int size);
	int Dir_Unlink(string path);
};

