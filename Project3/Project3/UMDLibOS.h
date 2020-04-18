#pragma once
#include "DirectoryAPI.h"
#include "DiskAPI.h"
#include "FileAccessAPI.h"
#include "FileSystemAPI.h"
#include <sstream>

#define MAX_FILES_AND_DIRECTORIES 100
#define NUM_SECTORS 1000


class UMDLibOS
{
private:
	static string osErrMsg;
	static string diskErrMsg;
public:
	static unique_ptr<DirectoryINode> rootDirectory;
	static bool DiskSectorBitmap[NUM_SECTORS];
	static bool INodeBitmap[NUM_SECTORS];
	static void inputSeekingLoop();
	static string getDiskErrorMsg();
	static string getOSErrorMsg();
	static void setDiskErrorMsg(string _diskErrMsg);
	static void setOSErrorMsg(string _osErrMsg);
	static int hexToDecimal(string hex);
	static string decimalToHex(int decimal);
};
