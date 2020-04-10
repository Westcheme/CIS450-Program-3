#pragma once
#include <string>
using namespace std;

class File
{
private:
	File subFiles;

public:
	int findFile(string name);
};

