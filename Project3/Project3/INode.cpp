#include "INode.h"


INode::INode()
{
	ID = IDCounter;
	IDCounter++;
	size = 0;
	name = "";
	for (int i = 0; i < MAX_FILE_SIZE; i++)
	{
		dataBlocks[i] = NULL;
	}
	numberDataBlocks = 0;
}

FileINode::FileINode()
{
	fileType = "File";
}

DirectoryINode::DirectoryINode()
{
	fileType = "Directory";
}

int DirectoryINode::getNumberSubDirectories()
{
	return numberSubDirectories;
}

void DirectoryINode::setNumberSubDirectories(int quantity)
{
	numberSubDirectories = quantity;
}

void DirectoryINode::addSubFile(unique_ptr<FileINode> subFile)
{
	size += subFile->getSize();
	subFiles.push_back(subFile);
}

void DirectoryINode::addSubDirectory(unique_ptr<DirectoryINode> subDirectory)
{
	subDirectories.push_back(subDirectory);
}


void INode::setName(string _name)
{
	name = _name;
}

string INode::getName()
{
	return name;
}

int INode::getNumberDataBlocks()
{
	return numberDataBlocks;
}

void INode::assignDataBlock(unique_ptr<DataBlock> dataBlock)
{
	numberDataBlocks++;
	dataBlocks.push_back(dataBlock);
}

int INode::getSize()
{
	return size;
}

int INode::getID()
{
	return ID;
}

int DirectoryINode::getSize()
{
	int size = 0;
	for (int i = 0; i < subDirectories.size; i++)
	{
		size += subDirectories[i]->getSize();
	}

	for (int i = 0; i < subFiles.size; i++)
	{
		size += subFiles[i]->getSize();
	}

	return size;

}