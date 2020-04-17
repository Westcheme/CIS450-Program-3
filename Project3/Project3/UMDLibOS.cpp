#include "UMDLibOS.h"


string getDiskErrorMsg()
{
	return diskErrMsg;
}
string getOSErrorMsg()
{
	return osErrMsg;
}

void setDiskErrorMsg(string _diskErrMsg)
{
	diskErrMsg = _diskErrMsg;
}

void setOSErrorMsg(string _osErrMsg)
{
	osErrMsg = _osErrMsg;
}

//Finds the file and returns its file descriptor
//If the file was not found return -1
int findFile(string file)
{

}
