#pragma once
#include "Simulation.cpp"
#include "INode.h"
#include "File.h"
#include <string>
using namespace std;

class FileAccessAPI
{
public:
	int File_Create(string file);
	int File_Open(string file);
	int File_Read(int fd, string buffer, int size);
	int File_Write(int fd, string buffer, int size);
	int File_Seek(int fd, int offset);
	int File_Close(int fd);
	int File_Unlink(string file);
};

