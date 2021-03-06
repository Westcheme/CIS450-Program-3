#pragma once
#include "DirectoryAPI.h"

DirectoryAPI::DirectoryAPI()
{
	//numDirectories = 0;
}

//Dir_Create() creates a new directory as named by path.
//Reminder, all paths are absolute paths, i.e., assume no tracking the current working.
//Creating a new directory takes a number of steps: first, you have to allocate a new file (of type directory), and then add a new directory entry in the current directory's parent.
//Upon failure of any kind, return -1 and set osErrMsg to E_DIR_CREATE.
//Upon success, return 0.
//Note that Dir_Create() is not recursive -- that is, if only "/" exists, and you want to create a directory "/a/b/", must first create "/a", and then create "/a/b"
int DirectoryAPI::Dir_Create(string path)
{
	&rootDirectory;
	//Files names must be accounted for in the 256 character path limit
	if (path.length() > 240)
	{
		cout << "Path cannot be greater than 256 characters, including future file names directory was not created";
		UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
		return -1;
	}
	else if (path == "")
	{
		cout << "Path name cannot be empty string, direcetory was not created";
		UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
		return -1;
	}
	else if (findDirectory(path) != NULL)	//TODO: Must find if there is a directory of the same name only in the current directory, if found do not create directory, cannot have duplicate directories
	{
		cout << "File Already Exists";
		UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
		return -1;
	}
	else
	{
		&rootDirectory;
		//cout << "Parent Directory Found";
		DirectoryINode* parentDirectory;
		DirectoryINode* newDirectory;
		string newDirectoryName;

		if (path.at(path.size() - 1) == '/')
			path = path.substr(0, path.size() - 1);

		//separates new directory name from existing path
		newDirectoryName = path.substr(path.find_last_of("/") + 1, path.size() - path.find_last_of("/")) + "/";
		
		if (newDirectoryName.size() > 15)
		{
			cout << "Directory Name must be 15 or less characters (do not include \"/\")";
			UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
			return -1;
		}
		
		path = path.substr(0, path.find_last_of("/") + 1);
		parentDirectory = findDirectory(path);

		//indicates error if the path does not exist
		if (parentDirectory == NULL)
		{
			cout << "Desired path cannot be created, parent does not exist.";
			UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
			return -1;
		}

		newDirectory = new DirectoryINode();
		newDirectory->setName(newDirectoryName);

		parentDirectory->addSubDirectory(newDirectory);

		numDirectories++;

		return 0;
	}
}

//Dir_Size() returns the number of bytes in the directory referred to by path.
//This routine should be used to find the size of the directory before calling Dir_Read() (described below) to find the contents of the directory.
int DirectoryAPI::Dir_Size(string path)
{
	DirectoryINode* targetDirectory;
	targetDirectory = findDirectory(path);

	if(targetDirectory == NULL)
	{
		cout << path << "Does not exist.";
		return -1;
	}

	return targetDirectory->getSize();

}

//Used to read the contents of a directory
//Returns in the buffer a set of directory entries, 20 bytes containing 16-byte names of 
//the directories and files within the directory named by path, followed by 4-byte integer INode
//If size is not big enough to contain all of the entries, return -1 and set osErrMsg to E_BUFFER_TOO_SMALL. 
//Otherwise, read the data into the buffer, and return the number of directory entries that are in the directory
int DirectoryAPI::Dir_Read(string path, string& buffer, int size)
{
	DirectoryINode* targetDirectory;
	string newEntry = "";
	string entryString = "";

	targetDirectory = findDirectory(path);

	if (targetDirectory == NULL) 
	{
		cout << "Specified directory does not exist.";
		UMDLibOS::setOSErrorMsg("DIR_NOT_FOUND");
		return -1;
	}


	for (int i = 0; i < targetDirectory->getNumberSubDirectories(); i++)
	{
		newEntry = targetDirectory->subDirectories[i]->getName();
		newEntry.append(string(16 - newEntry.size(), '0'));
		string hexString = UMDLibOS::decimalToHex(targetDirectory->subDirectories[i]->getID());
		hexString = string(4 - hexString.length(), '0').append(hexString);
		newEntry.append(hexString);
		entryString += newEntry;
	}

	for (int i = 0; i < targetDirectory->getNumberSubFiles(); i++)
	{
		newEntry = targetDirectory->subFiles[i]->getName();
		newEntry.append(string(16 - newEntry.size(), '0'));
		string hexString = UMDLibOS::decimalToHex(targetDirectory->subFiles[i]->getID());
		hexString = string(4 - hexString.length(), '0').append(hexString);
		newEntry.append(hexString);
		entryString += newEntry;
	}
	//if size is not big enough to contain all entries
	if (size < entryString.length()) {
		UMDLibOS::setOSErrorMsg("E_BUFFER_TOO_SMALL");
		return -1;
	}

	buffer = entryString;

	return 0;
}

//Removes a directory referred to by path, freeing up its inode and data blocks
//Dir_Unlink() should only be successful if there are no files within the directory.
//If there are still files within the directory, return -1 and set osErrMsg toE_DIR_NOT_EMPTY. 
//If someone tries to remove the root directory ("/"), don't allow them to do it! Return -1 and set osErrMsg to E_DEL_ROOT_DIR.
int DirectoryAPI::Dir_Unlink(string path)
{
	//if path is root directory ("/")
	if (!(path.compare("/"))) { //compare should return 0 when two strings are the same, -1 if path is comes first alphabetically, 1 if after
		cout << "You can't unlink the root directory";
		UMDLibOS::setOSErrorMsg("E_DEL_ROOT_DIR");
		return -1;
	}

	string parentPath = path.substr(0, path.find_last_of("/") + 1);
	DirectoryINode* parentDirectory = findDirectory(parentPath);

	DirectoryINode* targetDirectory = findDirectory(path);

	if (targetDirectory == NULL)
	{
		cout << "Target Directory does not exist.";
		UMDLibOS::setOSErrorMsg("E_DEL_DIR_NOT_FOUND");
		return -1;
	}

	//Check if directory is empty
	if (targetDirectory->getNumberSubDirectories() != 0 && targetDirectory->getNumberSubFiles() != 0) {
		cout << "Unable to unlink. Directory not empty";
		UMDLibOS::setOSErrorMsg("DIR_NOT_EMPTY");
		return -1;
	}

	//update number of directories in parent/adjust pointerArray
	parentDirectory->removeSubDirectory(targetDirectory->getName());

	return 0;
}

int DirectoryAPI::getNumDirectories()
{
	return numDirectories;
}


//HELPER METHODS:

DirectoryINode* DirectoryAPI::findDirectory(string path)
{
	DirectoryINode* currentINode;
	DirectoryINode* subINode;
	DirectoryINode* returnINode;
	char delimiter = '/';
	string foundString;

	currentINode = &rootDirectory;

	if (path == "/")
		return currentINode;
	
	//iterates through all DirectoryINodes until the desired directory INode is reached
	//possible valid input to consider:
	// "/a/a/"
	if (path[0] != '/')
		path = '/' + path;
	if (path[path.size() - 1] == '/')
		path = path.substr(0, path.size() - 1);
	int foundIndex = path.find(delimiter, 1);
	while (foundIndex >= 0) //loop while delimiters exist that aren't the first char
	{

		foundString = path.substr(1, path.find(delimiter, 1));
		path = path.substr(path.find(delimiter) + 1, path.size() - path.find(delimiter));
		for (int i = 0; i < currentINode->getNumberSubDirectories(); i++)
		{
			subINode = currentINode->subDirectories[i];
			if (subINode->getName() == foundString)
			{
				currentINode = subINode;
				continue;
			}
		}
		foundIndex = path.find(delimiter, 1);
	}
	//handles the last directory name
	foundString = path;

	//Format string to correctly match expected name
	if (foundString[0] == delimiter)
		foundString = foundString.substr(foundString.find(delimiter) + 1, foundString.length() - 1);
	if (foundString[foundString.length() - 1] != delimiter)
		foundString += delimiter;

	for (int i = 0; i < currentINode->getNumberSubDirectories(); i++)
	{
		if (currentINode->subDirectories[i]->getName() == foundString)
		{
			returnINode = currentINode->subDirectories[i];
			return returnINode;
		}
	}
	return NULL;

}


