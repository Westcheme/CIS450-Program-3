#include "DirectoryAPI.h"
#include "DiskAPI.h"
#include "FileAccessAPI.h"
#include "FileSystemAPI.h"

#pragma once
class UMDLibOS
{
private:
	string osErrMsg;
	string diskErrMsg;
public:
	string getDiskErrorMsg();
	string getOSErrorMsg();
	void setDiskErrorMsg(string _diskErrMsg);
	void setOSErrorMsg(string _osErrMsg);
};
