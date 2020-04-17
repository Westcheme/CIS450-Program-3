#include "DiskAPI.h"


int DiskAPI::Disk_Init()
{
	//Initialize all disk sectors to 0
	for (int i = 0; i < NUM_SECTORS; i++)
	{
		diskSectors[i].size = 0;
	}

	//Create the root directory
	DirectoryINode *rootDirectory = new DirectoryINode;
	rootDirectory->setName("Root");
	INodeBitmap[0] = 1;

	//Create the super block and store it to disk sector 0
	DataBlock *superBlock = new DataBlock;
	superBlock->size = 4;	//Magic Number
	diskSectors[0] = *superBlock;

	return 0;
}

int DiskAPI::Disk_Load()
{

}

int DiskAPI::Disk_Save()
{

}

int DiskAPI::Disk_Write(int sector, string buffer)
{

}

int DiskAPI::Disk_Read(int sector, string buffer)
{

}
