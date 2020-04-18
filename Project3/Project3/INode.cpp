#include "INode.h"


INode::INode()
{
	size = 0;
	name = "";
	for (int i = 0; i < MAX_FILE_SIZE; i++)
	{
		dataBlocks[i] = NULL;
	}
	numberDataBlocks = 0;
}

INode::~INode() 
{
	delete[numberDataBlocks] dataBlocks;
}

FileINode::FileINode()
{
	fileType = "File";
}

DirectoryINode::DirectoryINode()
{
	fileType = "Directory";
	subDirectories = NULL;
	subFiles = NULL;
}

DirectoryINode::~DirectoryINode()
{
	delete[numberSubFiles] subFiles;
	delete[numberSubDirectories] subDirectories;
}


void INode::setName(string _name)
{
	name = _name;
}