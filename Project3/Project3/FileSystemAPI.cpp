#include "FileSystemAPI.h"


//ANY ACCESS ATTEMPT WHILE FILE SYSTEM IS UNAVAILABLE return -1 and set osErrMsg to E_INVALID_ACCESS_ATTEMPT

//Called exactly once before any other UMDLibFS functions are called.
//Determines if the external disk image exists or not, if not then a new disk image is created.
//The external disk is then copied into the working disk and verified if it is in the file system.
//Success: return 0
//Failure: return -1 and set osErrMsg to E_FILE_BOOT
int FileSystemAPI::FS_Boot()
{

	if (false /*TODO: Check if disk image exists*/) {
		UMDLibOS::setOSErrorMsg("E_FILE_BOOT");
		bootSuccess = false;
		return -1;
	}

	bootSuccess = true;

	return 0;
}

//Makes sure the contents of the file system are stored persistently on disk.
//This copies the working disk image to the external disk image.
//return 0
int FileSystemAPI::FS_Sync()
{

	return 0;
}

//Calls FS_Sync() and then makes the files system unavailable for access until FS_Boot() is called.
//Success: return 0
//Failure: return -1 and set osErrMsg to E_FILE_RESET
int FileSystemAPI::FS_Reset()
{
	FS_Sync();

	if (false /*TODO: Check if reset fails*/) { //Under what circumstances does this fail? Perhaps if FS_Sync() fails?
		UMDLibOS::setOSErrorMsg("E_FILE_RESET");
		return -1;
	}

	bootSuccess = false;

	return 0;
}
