#include "INode.h"


INode::INode()
{
	ID = IDCounter;
	IDCounter++;
	size = 0;
	name = "";
	numberDataBlocks = 0;
	for (int i = 0; i < MAX_FILE_SIZE; i++)
	{
		dataBlocks[i] = 0;
	}
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

int DirectoryINode::getNumberSubFiles()
{
	return numberSubFiles;
}

void DirectoryINode::setNumberSubDirectories(int quantity)
{
	numberSubDirectories = quantity;
}

void DirectoryINode::addSubFile(FileINode* subFile)
{
	size += subFile->getSize();
	subFiles[numberSubFiles] = subFile;
	numberSubFiles++;
}

void DirectoryINode::addSubDirectory(DirectoryINode* subDirectory)
{
	subDirectories[numberSubDirectories] = subDirectory;
	numberSubDirectories++;
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

void INode::assignDataBlock(DataBlock* dataBlock)
{
	dataBlocks[numberDataBlocks] = dataBlock;
	numberDataBlocks++;
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
	for (int i = 0; i < numberSubDirectories; i++)
	{
		size += subDirectories[i]->getSize();
	}

	for (int i = 0; i < numberSubFiles; i++)
	{
		size += subFiles[i]->getSize();
	}

	return size;

}

int INode::getDataBlocksIndex(int index)
{
	return dataBlocks[index];
}

void INode::setDataBlocksIndex(int index, int diskSectorIndex)
{
	dataBlocks[index] = diskSectorIndex;
}