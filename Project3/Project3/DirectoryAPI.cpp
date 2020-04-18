#include "DirectoryAPI.h"


DirectoryAPI::DirectoryAPI()
{
	numDirectories = 0;
}

//Dir_Create() creates a new directory as named by path.
//Reminder, all paths are absolute paths, i.e., assume no tracking the current working.
//Creating a new directory takes a number of steps: first, you have to allocate a new file (of type directory), and then add a new directory entry in the current directory's parent.
//Upon failure of any kind, return -1 and set osErrMsg to E_DIR_CREATE.
//Upon success, return 0.
//Note that Dir_Create() is not recursive -- that is, if only "/" exists, and you want to create a directory "/a/b/", must first create "/a", and then create "/a/b"
int DirectoryAPI::Dir_Create(string path)
{
	if (path.length() > 256) cout << "Path cannot be greater than 256 characters, directory was not created";
	else if (path == "") cout << "Path name cannot be empty string, direcetory was not created";
	else if (findDirectory(path) >= 0)	//TODO: Must find if there is a directory of the same name only in the current directory, if found do not create directory, cannot have duplicate directories
	{
		UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
		return -1;
	}
	else
	{
		DirectoryINode* newDirectory = new DirectoryINode;
		newDirectory->setName(path);
		numDirectories++;
		return 0;
	}
}

//Dir_Size() returns the number of bytes in the directory referred to by path.
//This routine should be used to find the size of the directory before calling Dir_Read() (described below) to find the contents of the directory.
int DirectoryAPI::Dir_Size(string path)
{

}

//Used to read the contents of a directory
//Returns in the buffer a set of directory entries, 20 bytes containing 16-byte names of 
//the directories and files within the directory named by path, followed by 4-byte integer INode
//If size is not big enough to contain all of the entries, return -1 and set osErrMsg to E_BUFFER_TOO_SMALL. 
//Otherwise, read the data into the buffer, and return the number of directory entries that are in the directory
int DirectoryAPI::Dir_Read(string path, string buffer, int size)
{


	//if size is not big enough to contain all entries
	if (size < buffer.size) {
		UMDLibOS::setOSErrorMsg("E_BUFFER_TOO_SMALL");
		return -1;
	}

	return 0;
}

//Removes a directory referred to by path, freeing up its inode and data blocks
//Dir_Unlink() should only be successful if there are no files within the directory.
//If there are still files within the directory, return -1 and set osErrMsg toE_DIR_NOT_EMPTY. 
//If someone tries to remove the root directory ("/"), don't allow them to do it! Return -1 and set osErrMsg to E_DEL_ROOT_DIR.
int DirectoryAPI::Dir_Unlink(string path)
{

	string h = path.c_str("\\");


	//if path is root directory ("/")
	if (!(path.compare("/"))) { //compare should return 0 when two strings are the same, -1 if path is comes first alphabetically, 1 if after
		UMDLibOS::setOSErrorMsg("E_DEL_ROOT_DIR");
		return -1;
	}

	//Check if directory is empty
	if (false/*TODO: CHECK IF DIRECTORY IS EMPTY*/) {
		UMDLibOS::setOSErrorMsg("DIR_NOT_EMPTY");
		return -1;
	}

	return 0;
}

INode* DirectoryAPI::findDirectory(string path)
{

}

int DirectoryAPI::getNumDirectories()
{
	return numDirectories;
}
