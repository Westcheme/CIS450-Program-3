#include "DiskAPI.h"

//This method is called exactly once by the OS before any other disk operations take place
int DiskAPI::Disk_Init()
{

	//Initialize all data in sector to 0


	//Create superblock and empty root directory entries


	return 0;

}

//This method is called to load the contents of the external disk file system array
//into the working disk. This should be executed once while booting (in FS_Boot())
int DiskAPI::Disk_Load()
{


	return 0;
}

//This method saves the current in-memory working disk to the external disk.
//It saves the contents of an in-memory file system to the external file disk
//to be "booted" again later. This method should be invoked by FS_Sync
int DiskAPI::Disk_Save()
{
	

	return 0;
}

//Write the data in the buffer to the specified sector.
int DiskAPI::Disk_Write(int sector, string buffer)
{


	//If the indicated sector is out of bounds, or the buffer is null,
	//set the diskErrMsg attribute in Simulation to "E_READ_INVALID_PARAM"
}

//This method reads a specified sector into a specified buffer. The buffer and sector are assumed to be the same size.
int DiskAPI::Disk_Read(int sector, string buffer)
{


	//If the indicated sector is out of bounds, or the buffer is null,
	//set the diskErrMsg attribute in Simulation to "E_READ_INVALID_PARAM"
	if (false /*TODO: CHECK IF SECTOR IS OUT OF BOUNDS*/) {
		UMDLibOS::setDiskErrorMsg("E_READ_INVALID_PARAM");
		return -1;
	}

	return 0;
}
