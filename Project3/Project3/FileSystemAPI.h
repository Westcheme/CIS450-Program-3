#pragma once
#include "UMDLibOS.h"
class FileSystemAPI
{
public:
	int FS_Boot();
	int FS_Sync();
	int FS_Reset();
};
