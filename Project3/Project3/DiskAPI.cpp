#include "DiskAPI.h"

int DiskAPI::Disk_Init()
{
	//Initialize all disk sectors to 0
	for (int i = 0; i < NUM_SECTORS; i++)
	{
		externalDiskSectors[i]->get->size = 0;
		workingDiskSectors[i]->get->size = 0;
	}

	//Create the root directory if one does not already exist
	if (rootDirectory == NULL) {
		rootDirectory->get = new DirectoryINode;
		rootDirectory->get->setName("Root");
		INodeBitmap[0] = 1;
	}

	//Crate the super block and store it to disk sector 0
	DataBlock* superBlock = new DataBlock;
	superBlock->size = BLOCK_SIZE;
	assignDataBlockToDiskSector(0, superBlock);

	return 0;
}

//This method is called to load the contents of the external disk file system array
//into the working disk. This should be executed once while booting (in FS_Boot())
int DiskAPI::Disk_Load()
{

	if (externalDiskSectors[0]->get != NULL) //if external disk has a super block, load into working disk
	{
		for (int i = 0; i < NUM_SECTORS; i++) 
		{
			if(externalDiskSectors[i]->get != NULL)
			{
				//TODO: Get this to work in a way that copies values
				//rather than copying the reference
				DataBlock tempBlock;
				workingDiskSectors[i]->get = new DataBlock;
			}
			else
			{
				workingDiskSectors[i]->get = externalDiskSectors[i]->get->;
			}
		}
	}
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

//HELPER METHODS BELOW

void DiskAPI::assignDataBlockToDiskSector(int sector, DataBlock* dataBlock) {
	workingDiskSectors[sector] = dataBlock;
	DiskSectorBitmap[sector] = 1;
}