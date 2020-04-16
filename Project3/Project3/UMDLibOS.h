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


#pragma once
class UMDLibOS
{
private:
	static string osErrMsg;
	static string diskErrMsg;
public:
	static void inputSeekingLoop();
	static string getDiskErrorMsg();
	static string getOSErrorMsg();
	static void setDiskErrorMsg(string _diskErrMsg);
	static void setOSErrorMsg(string _osErrMsg);
	static void print(string _message);
	static void println(string _message);
};
