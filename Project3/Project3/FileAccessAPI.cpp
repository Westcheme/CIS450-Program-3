#include "FileAccessAPI.h"


FileAccessAPI::FileAccessAPI()
{
	numFiles = 0;
	numFilesOpen = 0;
	for (int i = 0; i < MAX_NUM_OPEN_FILES; i++)
	{
		openFiles[i] = NULL;
		filePointer[i] = 0;
	}
}

//Creates a new file of the name pointed to by file.
//If the file already exists return -1 and set osErrMsg to E_FILE_CREATE
//Success: return 0
//Failure: return -1 and set osErrMsg to E_FILE_CREATE
int FileAccessAPI::File_Create(string file)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}

	if (file[file.length() - 1] == '/')
		file = file.substr(0, file.size() - 1);

	string path = file.substr(0, file.find_last_of('/'));

	if (DirectoryAPI::findDirectory(path) == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_FILE_CREATE");
		cout << "The path does not exist, file was not created";
		return -1;
	}
	else if (file.length() > 15)
	{
		UMDLibOS::setOSErrorMsg("E_FILE_CREATE");
		cout << "File name cannot be greater than 15 characters, file was not created";
		return -1;
	}
	else if (file == "")
	{
		UMDLibOS::setOSErrorMsg("E_FILE_CREATE");
		cout << "File name cannot be empty string, file was not created";
		return -1;
	}
	else if (findFile(path, file) != NULL)
	{
		UMDLibOS::setOSErrorMsg("E_FILE_CREATE");
		cout << "File already already exists within this directory, file was not created";
		return -1;
	}
	else
	{
		cout << "File was created successfully";
		FileINode* newFile = new FileINode;
		newFile->setName(file);
		numFiles++;
		return 0;
	}
}

//Opens up a file and returns an integer file descriptor, which can be used to read from or write data to that file.
//If the file does not exist, return -1 and set osErrMsg to E_NO_SUCH_FILE
//If there are already maximum number of files open, return -1 and set osErrMsg to E_TOO_MANY_OPEN_FILES
int FileAccessAPI::File_Open(string file)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}


	if (file[file.length() - 1] == '/')
		file = file.substr(0, file.size - 1);

	string path = file.substr(0, file.find_last_of('/'));

	if (numFilesOpen == MAX_NUM_OPEN_FILES)
	{
		UMDLibOS::setOSErrorMsg("E_TOO_MANY_OPEN_FILES");
		return -1;
	}
	else if (findFile(path, file) == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_NO_SUCH_FILE");
		return -1;
	}
	else
	{
		cout << "Successfully opened file";
		int fileDescriptor = numFilesOpen;
		openFiles[fileDescriptor] = findFile(path, file);
		filePointer[fileDescriptor] = 0;
		numFilesOpen++;
		return fileDescriptor;
	}
}

//Read size bytes from the file referenced by the file descriptor fd.
//The data should be read into a buffer area buffer.
//All reads should begin at the current location of the file pointer, and file pointer should be updated after the read to the new location.
//If the file is not open, return -1 and set osErrMsg to E_READ_BAD_FD.
//If the file is open, the number of bytes actually read should be returned, which can be less than or equal to size.
//If the file pointer is already at the end of the file, zero should be returned.
int FileAccessAPI::File_Read(int fd, string& buffer, int size)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}


	if (openFiles[fd] == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_READ_BAD_FD");
		return -1;
	}
	else if (filePointer[fd] == (openFiles[fd]->getSize() - 1))
	{
		return 0;
	}
	else
	{
		buffer = "";
		string tempBuffer;
		int count = 0;
		int bytesRead;
		int dataBlockIndexStart = ceil(filePointer[fd] / 512);
		int dataBlockIndexEnd = ceil((filePointer[fd] + size) / 512);

		if ((openFiles[fd].get->size - filePointer[fd]) / size >= 1)
		{
			bytesRead = size;

			for (int i = 0; i < openFiles[fd]->getNumberDataBlocks(); i++)
			{
				DiskAPI::Disk_Read(openFiles[fd].get->dataBlocksIndex[i], tempBuffer);

				if (i == 0)
				{
					for (int j = filePointer[fd]; j < 512; j++)
					{
						buffer[count] += tempBuffer[j];
						count++;
					}
				}
				else if (i == openFiles[fd]->getNumberDataBlocks()-1)
				{
					for (int j = 0; j < filePointer[fd] + size - 512; j++)
					{
						buffer[count] += tempBuffer[j];
						count++;
					}
				}
				else
				{
					for (int j = 0; j < 512; j++)
					{
						buffer[count] += tempBuffer[j];
						count++;
					}
				}
			}

			filePointer[fd] = filePointer[fd] + size;
		}
		else
		{
			bytesRead = openFiles[fd].get->size - filePointer[fd];

			for (int i = 0; i < openFiles[fd]->getNumberDataBlocks(); i++)
			{
				DiskAPI::Disk_Read(openFiles[fd].get->dataBlocksIndex[i], tempBuffer);

				if (i == 0)
				{
					for (int j = filePointer[fd]; j < 512; j++)
					{
						buffer[count] += tempBuffer[j];
						count++;
					}
				}
				else if (i == openFiles[fd]->getNumberDataBlocks() - 1)
				{
					for (int j = 0; j < filePointer[fd] + size - 512; j++)
					{
						buffer[count] += tempBuffer[j];
						count++;
					}
				}
				else
				{
					for (int j = 0; j < 512; j++)
					{
						buffer[count] += tempBuffer[j];
						count++;
					}
				}
			}

			filePointer[fd] = openFiles[fd].get->size - 1;
		}

		cout << "The specified file has been read from";
		return bytesRead;
	}
}

//Write size bytes from buffer and write them into the file referenced by fd.
//All writes should begin at the current location of the file pointer and the file pointer should be updated after the write to its current location plus size.
//Note that writes are the only way to extend the size of a file.
//If the file is not open, return -1 and set osErrMsg to E_BAD_FD.
//Success: all of the data should be written out to disk and the value of size should be returned.
//If the write cannot complete (due to lack of space), return -1 and set osErrMsg to E_NO_SPACE.
//If the file exceeds the maximum file size, return -1 and set osErrMsg to E_FILE_TOO_BIG.
int FileAccessAPI::File_Write(int fd, string buffer, int size)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}


	if (openFiles[fd] == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_BAD_FD");
		return -1;
	}
	else if (openFiles[fd]->getSize() > MAX_FILE_SIZE * 512)
	{
		UMDLibOS::setOSErrorMsg("E_FILE_TOO_BIG");
		return -1;
	}
	else if (MAX_FILE_SIZE * 512 - filePointer[fd] < size)
	{
		UMDLibOS::setOSErrorMsg("E_NO_SPACE");
		return -1;
	}
	else
	{
		int numDiskSectorsNeeded = ceil(size / 512);
		int count = 0;

		string subBuffers[10];
		for (int i = 0; i < numDiskSectorsNeeded; i++)
		{
			for (int j = 0; j < 512; j++)
			{
				subBuffers[i][j] = buffer[j+(512*i)];
			}
		}

		for (int i = 0; i < NUM_SECTORS; i++)
		{
			if (DiskSectorBitmap[i] == 0)
			{
				openFiles[fd].get->dataBlocksIndex[count] = i;
				DiskAPI::Disk_Write(i, subBuffers[i]);
				count++;
				if (count == numDiskSectorsNeeded) break;
			}
		}

		filePointer[fd] = filePointer[fd] + size;
	}

	cout << "File was written successfully";
	return size;
}

//Update the current file location of the file pointer.
//The location is given as an offset from the beginning of the file.
//If offset is larger than the size of the file or negative, return -1 and set osErrMsg to E_SEEK_OUT_OF_BOUNDS.
//If the file is not currently open, return -1 and set osErrMsg to E_SEEK_BAD_FD.
//Success: return the new location of the file pointer.
int FileAccessAPI::File_Seek(int fd, int offset)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}


	if (openFiles[fd] == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_SEEK_BAD_FD");
		return -1;
	}
	else if (offset < 0 || offset > openFiles[fd].get->size * 512)
	{
		UMDLibOS::setOSErrorMsg("E_SEEK_OUT_OF_BOUNDS");
		return -1;
	}
	else
	{
		cout << "Location in file found";
		filePointer[fd] = offset;
		return filePointer[fd];
	}
}

//Close the file referred to by file descriptor fd.
//If the file is not open, return -1 and set osErrMsg to E_CLOSE_BAD_FD.
//Success: return 0
int FileAccessAPI::File_Close(int fd)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}


	if (openFiles[fd] == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_CLOSE_BAD_FD");
		return -1;
	}
	else
	{
		cout << "File has been successfully closed";
		openFiles[fd] == NULL;
		filePointer[fd] = 0;
		return 0;
	}
}

//This should delete the file referenced by file, including removing its name from the directory it is in,
//and freeing up any data blocks and inodes that the file was using.
//If the file does not currently exist, return -1 and set osErrMsg to E_NO_SUCH_FILE.
//If the file is currently open, return -1 and set osErrMsg to E_FILE_IN_USE (and do NOT delete the file).
//Upon success, return 0.
int FileAccessAPI::File_Unlink(string file)
{
	if (!fs_available)
	{
		cout << "File System not available: Disk not booted.";
		UMDLibOS::setOSErrorMsg("FS_NOT_BOOTED");
		return -1;
	}


	if (file[file.length() - 1] == '/')
		file = file.substr(0, file.size - 1);

	string path = file.substr(0, file.find_last_of('/'));

	for (int i = 0; i < numFilesOpen; i++)
	{
		if (openFiles[i].get->name == file)
		{
			UMDLibOS::setOSErrorMsg("E_FILE_IN_USE");
			return -1;
		}
	}

	if (findFile(path, file) == NULL)
	{
		UMDLibOS::setOSErrorMsg("E_NO_SUCH_FILE");
		return -1;
	}
	else
	{
		string zeroString = "";
		for (int i = 0; i < 512; i++)
		{
			zeroString += "0";
		}

		unique_ptr<DirectoryINode> fileDirectory = DirectoryAPI::findDirectory(path);
		unique_ptr<FileINode> fileINode = findFile(path, file);
		int diskSectorIndex;

		for (int i = 0; i < fileDirectory->getNumberSubFiles; i++)
		{
			if (fileDirectory->subFiles[i]->getName() == file)
			{
				fileDirectory->subFiles[i] = NULL;
			}
		}

		for (int i = 0; i < fileINode.get->numberDataBlocks; i++)
		{
			diskSectorIndex = fileINode.get->dataBlocksIndex[i];
			DiskSectorBitmap[diskSectorIndex] = 0;
			DiskAPI::Disk_Write(diskSectorIndex, zeroString);
		}

		cout << "File was successfully deleted";
		return 0;
	}
}


//HEPLER METHODS BELOW:

//
shared_ptr<FileINode> FileAccessAPI::findFile(string path, string file)
{
	shared_ptr<DirectoryINode> fileDirectory = DirectoryAPI::findDirectory(path);

	for (int i = 0; i < fileDirectory->getNumberSubFiles(); i++)
	{
		if (fileDirectory->subFiles[i]->getName() == file)
		{
			return fileDirectory->subFiles[i];
		}
	}g
}

int FileAccessAPI::getNumFiles()
{
	return numFiles;
}