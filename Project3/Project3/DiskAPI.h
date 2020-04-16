#pragma once
#include "INode.h"
#include <string>
using namespace std;

#define NUM_SECTORS 1000
#define SECTOR_SIZE 512


class DiskAPI
{
private:
	DataBlock diskSectors[NUM_SECTORS];
	bool INodeBitmap[NUM_SECTORS];

public:
	int Disk_Init();
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector, string buffer);
	int Disk_Read(int sector, string buffer);
};

