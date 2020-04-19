#pragma once
#include "UMDLibOS.h"
using namespace std;

#define NUM_SECTORS 1000
#define SECTOR_SIZE 512
#define MAGIC_NUMBER '4'

class UMDLibOS;
static DataBlock* externalDiskSectors[NUM_SECTORS];
static DataBlock* workingDiskSectors[NUM_SECTORS];

class DiskAPI
{
private:
public:
	static int Disk_Init();
	static int Disk_Load();
	static int Disk_Save();
	static int Disk_Write(int sector, string buffer);
	static int Disk_Read(int sector, string& buffer);
	static void assignDataBlockToDiskSector(int sector, DataBlock* dataBlock);
};

