#pragma once
#include "FileType.h"
#include "DataBlock.h"
#include <list>

class INode
{
private:
	int fileSize;
	FileType fileType;
	list <DataBlock> dataBlocks;
};

