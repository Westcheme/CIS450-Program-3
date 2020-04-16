#include "UMDLibOS.h"


class UMDLibOS {

public: 

	string osErrMsg;

	string UMDLibOS::getDiskErrorMsg()
	{
		return diskErrMsg;
	}
	string UMDLibOS::getOSErrorMsg()
	{
		return osErrMsg;
	}

	void UMDLibOS::setDiskErrorMsg(string _diskErrMsg)
	{
		diskErrMsg = _diskErrMsg;
	}

	void UMDLibOS::setOSErrorMsg(string _osErrMsg)
	{
		osErrMsg = _osErrMsg;
	}

};
