#include "INode.h"


INode::INode()
{
	ID = IDCounter;
	IDCounter++;
	size = 0;
	name = "";
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

int DirectoryINode::getNumberSubFiles()
{
	return numberSubFiles;
}

void DirectoryINode::setNumberSubDirectories(int quantity)
{
	numberSubDirectories = quantity;
}

void DirectoryINode::addSubFile(shared_ptr<FileINode> subFile)
{
	size += subFile->getSize();
	subFiles[numberSubFiles].reset(subFile.get());
	numberSubFiles++;
}

void DirectoryINode::addSubDirectory(shared_ptr<DirectoryINode> subDirectory)
{
	subDirectories[numberSubDirectories].reset(subDirectory.get());
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

void INode::assignDataBlock(shared_ptr<DataBlock> dataBlock)
{
	dataBlocks[numberDataBlocks].reset(dataBlock.get());
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