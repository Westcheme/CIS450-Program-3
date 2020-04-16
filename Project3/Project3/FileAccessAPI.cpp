#include "FileAccessAPI.h"


//Creates a new file of the name pointed to by file.
//If the file already exists return -1 and set osErrMsg to E_FILE_CREATE
//Success: return 0
//Failure: return -1 and set osErrMsg to E_FILE_CREATE
int FileAccessAPI::File_Create(string file)
{
	if (file.length() > 15) cout << "File name cannot be greater than 15 characters, file was not created";
	else if (findFile(file) == -1)
	{
		UMDLisbOS::setOSErrMsg = "E_FILE_CREATE";
		return -1;
	}
	else
	{
		File* newFile = new File;
		newFile->setName(file);
		newFile->setFD(numFiles);
		numFiles++;
	}
}

//Opens up a file and returns an integer file descriptor, which can be used to read from or write data to that file.
//If the file does not exist, return -1 and set osErrMsg to E_NO_SUCH_FILE
//If there are already maximum number of files open, return -1 and set osErrMsg to E_TOO_MANY_OPEN_FILES
int FileAccessAPI::File_Open(string file)
{
	if (numFilesOpen == MAX_NUM_OPEN_FILES)
	{
		setDiskErrorMsg("E_TOO_MANY_OPEN_FILES");
		return -1;
	}
	else if (findFile(file) == -1)
	{
		osErrMsg = "E_NO_SUCH_FILE";
		return -1;
	}
	else
	{
		numFilesOpen++;
		return findFile(file);
	}
}

//Read size bytes from the file referenced by the file descriptor fd.
//The data should be read into a buffer area buffer.
//All reads should begin at the current location of the file pointer, and file pointer should be updated after the read to the new location.
////If the file is not open, return -1 and set osErrMsg to E_READ_BAD_FD.
//If the file is open, the number of bytes actually read should be returned, which can be less than or equal to size.
//If the file pointer is already at the end of the file, zero should be returned.
int FileAccessAPI::File_Read(int fd, string buffer, int size)
{

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

}

//Update the current file location of the file pointer.
//The location is given as an offset from the beginning of the file.
//If offset is larger than the size of the file or negative, return -1 and set osErrMsg to E_SEEK_OUT_OF_BOUNDS.
//If the file is not currently open, return -1 and set osErrMsg to E_SEEK_BAD_FD.
//Success: return the new location of the file pointer.
int FileAccessAPI::File_Seek(int fd, int offset)
{

}

//Close the file referred to by file descriptor fd.
//If the file is not open, return -1 and set osErrMsg to E_CLOSE_BAD_FD.
//Success: return 0
int FileAccessAPI::File_Close(int fd)
{

}

//
int FileAccessAPI::File_Unlink(string file)
{

}

int FileAccessAPI::findFile(string file)
{

}