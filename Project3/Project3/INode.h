#pragma once
#include <list>
#include <string>
#include <memory>
#include <vector>
using namespace std;

#define MAX_FILE_SIZE 10
#define MAX_FILES 100


static int IDCounter = 0; //Should only ever be referenced by INode



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
	int ID;
	string name; //In a real Linux file system, the name of the file would not be stored in the INode, but 
	string fileType;
	int dataBlocksIndex[10]; //Maximum number of 10 referenced by an INode
	int numberDataBlocks;
public:
	INode();
	void setName(string name);
	string getName();
	int getNumberDataBlocks();
	void assignDataBlock(int dataBlockIndex);
	int getSize();
	int getID();
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
	int numberSubFiles = 0;
	int numberSubDirectories = 0;
public:
	DirectoryINode();
	shared_ptr<FileINode>* subFiles;
	shared_ptr<DirectoryINode>* subDirectories;
	int getNumberSubDirectories();
	int getNumberSubFiles();
	void setNumberSubDirectories(int quantity);
	void addSubFile(shared_ptr<FileINode> subFile);
	void addSubDirectory(shared_ptr<DirectoryINode> subDirectory);
	int getSize();
};