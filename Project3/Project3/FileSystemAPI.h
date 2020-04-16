#pragma once
#include "UMDLibOS.h"
class FileSystemAPI
{
public:
	bool bootSuccess = false;
	int FS_Boot();
	int FS_Sync();
	int FS_Reset();
};
