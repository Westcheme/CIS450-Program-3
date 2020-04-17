#include "DiskAPI.h"

int DiskAPI::Disk_Init()
{
	string zeroString = "";
	for (int i = 0; i < SECTOR_SIZE; i++) {
		zeroString += "0";
	}

	//Initialize all data in disk sectors to 0
	for (int i = 0; i < NUM_SECTORS; i++)
	{
		DataBlock* dataBlock = new DataBlock;
		dataBlock->byteStream = zeroString;
		dataBlock->ID = i;
		dataBlock->size = 0;

		externalDiskSectors[i]->get = dataBlock;
		workingDiskSectors[i]->get = dataBlock;
	}

	//Create the root directory if one does not already exist
	if (rootDirectory == NULL) {
		rootDirectory->get = new DirectoryINode;
		rootDirectory->get->setName("Root");
		INodeBitmap[0] = 1;
	}

	//Crate the super block and store it to disk sector 0
	unique_ptr<DataBlock>* superBlock = new unique_ptr<DataBlock>();
	superBlock->get->size = SECTOR_SIZE;
	superBlock->get->byteStream = MAGIC_NUMBER;
	superBlock->get->size = 1;
	assignDataBlockToDiskSector(0, superBlock);

	return 0;
}

//This method is called to load the contents of the external disk file system array
//into the working disk. This should be executed once while booting (in FS_Boot())
int DiskAPI::Disk_Load()
{

	if (externalDiskSectors == NULL || externalDiskSectors[0]->get == NULL) //if external disk has a super block, load into working disk
	{
		return -1;
	}
	else {
		if (externalDiskSectors[0]->get->byteStream[0] == MAGIC_NUMBER) {
			return -1;
		}
	}

	string zeroString = "";
	for (int i = 0; i < SECTOR_SIZE; i++) {
		zeroString += "0";
	}

	//Copy DataBlocks from externalDisk into workingDisk
	for (int i = 0; i < NUM_SECTORS; i++) 
	{
		if(externalDiskSectors[i]->get != NULL)
		{
			DataBlock tempBlock;

			tempBlock.byteStream = externalDiskSectors[i]->get->byteStream;
			tempBlock.ID = externalDiskSectors[i]->get->ID;
			tempBlock.size = externalDiskSectors[i]->get->size;

			workingDiskSectors[i]->get = tempBlock;
		}
		else
		{
			DataBlock tempBlock;
			tempBlock.byteStream = zeroString;
			tempBlock.ID = i;
			tempBlock.size = 0;

			workingDiskSectors[i]->get = tempBlock;
		}
	}
	return 0;
}

//This method saves the current in-memory working disk to the external disk.
//It saves the contents of an in-memory file system to the external file disk
//to be "booted" again later. This method should be invoked by FS_Sync
int DiskAPI::Disk_Save()
{

	string zeroString = "";
	for (int i = 0; i < SECTOR_SIZE; i++) {
		zeroString += "0";
	}

	//Copy DataBlocks from workingDisk into externalDisk
	for (int i = 0; i < NUM_SECTORS; i++)
	{
		if (workingDiskSectors[i]->get != NULL)
		{
			DataBlock tempBlock;

			tempBlock.byteStream = workingDiskSectors[i]->get->byteStream;
			tempBlock.ID = workingDiskSectors[i]->get->ID;
			tempBlock.size = workingDiskSectors[i]->get->size;

			externalDiskSectors[i]->get = tempBlock;
		}
		else
		{
			DataBlock tempBlock;
			tempBlock.byteStream = zeroString;
			tempBlock.ID = i;
			tempBlock.size = 0;

			externalDiskSectors[i]->get = tempBlock;
		}
	}

	return 0;
}

//Write the data in the buffer to the specified sector.
//The buffer is assumed to be the same size as SECTOR_SIZE
int DiskAPI::Disk_Write(int sector, string buffer)
{
	//If the indicated sector is out of bounds, or the buffer is null,
	//set the diskErrMsg attribute in Simulation to "E_READ_INVALID_PARAM"
	if (sector < 0 || sector > NUM_SECTORS || buffer == "") {
		UMDLibOS::setDiskErrorMsg("E_READ_INVALID_PARAM");
		return -1;
	}

	workingDiskSectors[sector]->get->byteStream = buffer;

	return 0;
}

//This method reads a specified sector into a specified buffer. The buffer and sector are assumed to be the same size.
int DiskAPI::Disk_Read(int sector, string* buffer)
{
	//If the indicated sector is out of bounds, or the buffer is null,
	//set the diskErrMsg attribute in Simulation to "E_READ_INVALID_PARAM"
	if (sector < 0 || sector > NUM_SECTORS || buffer == NULL) {
		UMDLibOS::setDiskErrorMsg("E_READ_INVALID_PARAM");
		return -1;
	}

	buffer = workingDiskSectors[sector]->get->byteStream;

	return 0;
}

//HELPER METHODS BELOW

void DiskAPI::assignDataBlockToDiskSector(int sector, unique_ptr<DataBlock>* dataBlock) {
	workingDiskSectors[sector] = dataBlock;
	DiskSectorBitmap[sector] = 1;
}