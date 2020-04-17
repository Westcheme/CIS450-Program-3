#include "DirectoryAPI.h"
#include "DiskAPI.h"
#include "FileAccessAPI.h"
#include "FileSystemAPI.h"

#define MAX_FILES_AND_DIRECTORIES 100

string osErrMsg;
string diskErrMsg;

string getDiskErrorMsg();
string getOSErrorMsg();
void setDiskErrorMsg(string _diskErrMsg);
void setOSErrorMsg(string _osErrMsg);
int findFile(string file);


#pragma once
class UMDLibOS
{

};
