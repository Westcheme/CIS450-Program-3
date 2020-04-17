#pragma once
#include <list>
#include <string>
#include <memory>
using namespace std;

#define MAX_FILE_SIZE 10
#define MAX_FILES 100


struct DataBlock
{
public: 
	int byteStream;
	int ID;
	int size;
	int startFD;
};


class INode
{
protected:
	int size;
	string name; //In a real Linux file system, the name of the file would not be stored in the INode, but 
	string fileType;
	unique_ptr<DataBlock>* dataBlocks;
	int numberDataBlocks;
public:
	INode();
	~INode();
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
	unique_ptr<FileINode>* subFiles;
	unique_ptr<DirectoryINode>* subDirectories;
	int numberSubFiles = 0;
	int numberSubDirectories = 0;
public:
	DirectoryINode();
	~DirectoryINode();
};