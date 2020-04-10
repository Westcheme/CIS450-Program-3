#pragma once
#include "FileType.h"
#include "DataBlock.h"
#include <list>

class INode
{
private:
	list <DataBlock> dataBlocks;
	int fileSize;
	FileType fileType;
};

