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

int DirectoryINode::getNumbersubFiles()
{
	return numberSubFiles;
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

void INode::assignDataBlock(int dataBlockID)
{
	dataBlocks[numberDataBlocks] = dataBlockID;
	numberDataBlocks++;
}

int* INode::getAssignedDataBlocks(int& size)
{
	return dataBlocks;
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

void DirectoryINode::removeSubDirectory(string name)
{
	bool foundDirectory = false;
	//If null subdirectory is referenced, the method that called this incorrectly identified subdirectory name or parent name
	for (int i = 0; i < 100; i++)
	{
		if (subDirectories[i]->getName() == name)
		{
			delete subDirectories[i];

			if(subDirectories[i] !=  NULL)
				subDirectories[i] = NULL;

			foundDirectory = true;

			numberSubDirectories--;
			return;
		}

		if (foundDirectory && i == 99)
			subDirectories[i] = NULL;

		if (foundDirectory && i < 99)
		{
			if (subDirectories[i] == NULL)
				return;
			subDirectories[i] = subDirectories[i + 1];
		}

	}
}
int INode::getDataBlocksIndex(int index)
{
	return dataBlocks[index];
}

void INode::setDataBlocksIndex(int index, int diskSectorIndex)
{
	dataBlocks[index] = diskSectorIndex;
}
