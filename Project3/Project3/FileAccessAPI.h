#pragma once
#include "UMDLibOS.h"
#include "INode.h"
#include <iostream>
using namespace std;
#define MAX_NUM_OPEN_FILES 10


class FileAccessAPI
{
private:
	int numFiles;
	int numFilesOpen;
	int *filePointer[MAX_NUM_OPEN_FILES];
public:
	FileAccessAPI();
	int File_Create(string file);
	int File_Open(string file);
	int File_Read(int fd, string buffer, int size);
	int File_Write(int fd, string buffer, int size);
	int File_Seek(int fd, int offset);
	int File_Close(int fd);
	int File_Unlink(string file);
	int findFile(string file);
	int getNumFiles();
};
