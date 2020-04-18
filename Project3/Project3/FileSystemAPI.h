#pragma once
#include "UMDLibOS.h"
class FileSystemAPI
{
private:
	bool bootSuccess = false;
public:
	int FS_Boot();
	int FS_Sync();
	int FS_Reset();
};
