#pragma once
#include "UMDLibOS.h"
#include "INode.h"
#include <string>
#include <iostream>
#include <istream>
#include <vector>
using namespace std;

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
	unique_ptr<DirectoryINode> findDirectory(string path);
};

