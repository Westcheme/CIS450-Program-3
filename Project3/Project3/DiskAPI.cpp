#include "UMDLibOS.h"
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
		DataBlock* dataBlock = new DataBlock();
		dataBlock->byteStream = zeroString;
		dataBlock->ID = i;
		dataBlock->size = 0;

		DataBlock* dataBlock1 = new DataBlock();
		dataBlock1->byteStream = zeroString;
		dataBlock1->ID = i;
		dataBlock1->size = 0;

		externalDiskSectors[i].reset(dataBlock);
		workingDiskSectors[i].reset(dataBlock1);
	}
	
	//Create the root directory if one does not already exist
	if (rootDirectory.get() == NULL) {
		rootDirectory.reset(new DirectoryINode());
		rootDirectory->setName("Root");
		INodeBitmap[0] = 1;
	}

	//Crate the super block and store it to disk sector 0
	shared_ptr<DataBlock> superBlock = make_unique<DataBlock>();
	superBlock->size = SECTOR_SIZE;
	superBlock->byteStream = MAGIC_NUMBER;
	superBlock->size = 1;
	assignDataBlockToDiskSector(0, superBlock);

	return 0;
}

//This method is called to load the contents of the external disk file system array
//into the working disk. This should be executed once while booting (in FS_Boot())
int DiskAPI::Disk_Load()
{

	if (externalDiskSectors == NULL || externalDiskSectors[0] == NULL) //if external disk has a super block, load into working disk
	{
		return -1;
	}
	else {
		if (externalDiskSectors[0]->byteStream[0] == MAGIC_NUMBER) {
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
		if(externalDiskSectors[i] != NULL)
		{

			workingDiskSectors[i]->byteStream = externalDiskSectors[i]->byteStream;
			workingDiskSectors[i]->ID = externalDiskSectors[i]->ID;
			workingDiskSectors[i]->size = externalDiskSectors[i]->size;
		}
		else
		{
			workingDiskSectors[i]->byteStream = zeroString;
			workingDiskSectors[i]->ID = i;
			workingDiskSectors[i]->size = 0;
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
		if (workingDiskSectors[i] != NULL)
		{
			externalDiskSectors[i]->byteStream = workingDiskSectors[i]->byteStream;
			externalDiskSectors[i]->ID = workingDiskSectors[i]->ID;
			externalDiskSectors[i]->size = workingDiskSectors[i]->size;
		}
		else
		{
			externalDiskSectors[i]->byteStream = zeroString;
			externalDiskSectors[i]->ID = i;
			externalDiskSectors[i]->size = 0;
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

	workingDiskSectors[sector]->byteStream = buffer;

	return 0;
}

//This method reads a specified sector into a specified buffer. The buffer and sector are assumed to be the same size.
int DiskAPI::Disk_Read(int sector, string& buffer)
{
	//If the indicated sector is out of bounds, or the buffer is null,
	//set the diskErrMsg attribute in Simulation to "E_READ_INVALID_PARAM"
	if (sector < 0 || sector > NUM_SECTORS /*|| buffer == NULL/*buffer cannot be NULL*\/*/) {
		UMDLibOS::setDiskErrorMsg("E_READ_INVALID_PARAM");
		return -1;
	}

	buffer = workingDiskSectors[sector]->byteStream;

	return 0;
}

//HELPER METHODS BELOW

void DiskAPI::assignDataBlockToDiskSector(int sector, shared_ptr<DataBlock>& dataBlock) {
	workingDiskSectors[sector]->byteStream = dataBlock->byteStream;
	workingDiskSectors[sector]->ID = sector;
	workingDiskSectors[sector]->size = dataBlock->byteStream.size();
	DiskSectorBitmap[sector] = 1;
}