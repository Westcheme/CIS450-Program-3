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
