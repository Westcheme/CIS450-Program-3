#pragma once
#include <string>
using namespace std;

class DiskAPI
{
public:
	int Disk_Init();
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector, string buffer);
	int Disk_Read(int sector, string buffer);
};

