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
	string byteStream; //Stores data written to disk from a buffer string (512 bytes/characters)
	int ID; //Unique identifier for DataBlock, array index in the disk
	int size;
	//int startFD; Not necessary, since INode is used to refer to DataBlock
	//Above originially used to indicate starting address of DataBlock,
	//but byteStream character index 0 is the start of the DataBlock
};


class INode
{
protected:
	int size;
	string name; //In a real Linux file system, the name of the file would not be stored in the INode, but 
	string fileType;
	unique_ptr<DataBlock>* dataBlocks; //Maximum number of 10 referenced by an INode
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