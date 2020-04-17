#include "DirectoryAPI.h"
#include "DiskAPI.h"
#include "FileAccessAPI.h"
#include "FileSystemAPI.h"

#define MAX_FILES_AND_DIRECTORIES 100


#pragma once
class UMDLibOS
{
private:

	char* externalDisk;
	char* workingDisk;
	static string osErrMsg;
	static string diskErrMsg;
public:
	static void inputSeekingLoop();
	static string getDiskErrorMsg();
	static string getOSErrorMsg();
	static void setDiskErrorMsg(string _diskErrMsg);
	static void setOSErrorMsg(string _osErrMsg);
};
