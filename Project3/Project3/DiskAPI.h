#pragma once
#include "INode.h"
#include <string>
#include "UMDLibOS.h"
using namespace std;

#define NUM_SECTORS 1000
#define SECTOR_SIZE 512
#define BLOCK_SIZE 4


class DiskAPI
{
private:
	unique_ptr<DirectoryINode>* rootDirectory = NULL;
	unique_ptr<DataBlock>* externalDiskSectors[NUM_SECTORS];
	unique_ptr<DataBlock>* workingDiskSectors[NUM_SECTORS];
	bool INodeBitmap[NUM_SECTORS];
	bool DiskSectorBitmap[NUM_SECTORS];
public:
	int Disk_Init();
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector, string buffer);
	int Disk_Read(int sector, string buffer);
	void assignDataBlockToDiskSector(int sector, DataBlock *dataBlock);
};

