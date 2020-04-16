#pragma once
#include <list>
#include <string>
using namespace std;

#define MAX_FILE_SIZE 10
#define MAX_FILES 100


struct DataBlock
{
	int byteStream;
	int ID;
	int size;
	int startFD;
};


class INode
{
protected:
	int size;
	string name;
	string fileType;
	DataBlock *dataBlocks;
public:
	INode();
	void setName(string name);
};


class FileINode : public INode
{
private:

public:
	FileINode();
};


class DirectoryINode : public INode
{
private:
	FileINode *subFiles;
	DirectoryINode *subDirectories;
public:
	DirectoryINode();
};