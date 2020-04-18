#pragma once
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
		UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
		return -1;
	}
	else
	{

		unique_ptr<DirectoryINode> parentDirectory;
		unique_ptr<DirectoryINode> newDirectory;
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
		
		path = path.substr(0, path.find_last_of("/"));
		parentDirectory = findDirectory(path);

		//indicates error if the path does not exist
		if (parentDirectory == NULL)
		{
			cout << "Desired path cannot be created, parent does not exist.";
			UMDLibOS::setOSErrorMsg("E_DIR_CREATE");
			return -1;
		}

		newDirectory->setName(newDirectoryName);

		parentDirectory->addSubDirectory(unique_ptr<DirectoryINode>(newDirectory.get()));

		numDirectories++;

		return 0;
	}
}

//Dir_Size() returns the number of bytes in the directory referred to by path.
//This routine should be used to find the size of the directory before calling Dir_Read() (described below) to find the contents of the directory.
int DirectoryAPI::Dir_Size(string path)
{
	unique_ptr<DirectoryINode> targetDirectory;
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
	unique_ptr<DirectoryINode> targetDirectory;
	string newEntry = "";
	string entryString = "";
	int entrySize = 0;

	targetDirectory = findDirectory(path);

	if (targetDirectory == NULL) 
	{
		cout << "Specified directory does not exist.";
		UMDLibOS::setOSErrorMsg("DIR_NOT_FOUND");
		return -1;
	}


	for (int i = 0; i < targetDirectory.get()->getNumberSubDirectories(); i++)
	{
		newEntry = targetDirectory->subDirectories[i]->getName();
		newEntry.append(string(16 - newEntry.size(), '0'));
		newEntry.append(UMDLibOS::decimalToHex(targetDirectory->subDirectories[i]->getID()));
		entryString += newEntry;
	}

	for (int i = 0; i < targetDirectory.get()->getNumberSubFiles(); i++)
	{
		newEntry = targetDirectory->subFiles[i]->getName();
		newEntry.append(string(16 - newEntry.size(), '0'));
		newEntry.append(UMDLibOS::decimalToHex(targetDirectory->subFiles[i]->getID()));
		entryString += newEntry;
	}
	//if size is not big enough to contain all entries
	if (size < entrySize) {
		UMDLibOS::setOSErrorMsg("E_BUFFER_TOO_SMALL");
		return -1;
	}

	buffer = entryString;

	return entrySize;
}

//Removes a directory referred to by path, freeing up its inode and data blocks
//Dir_Unlink() should only be successful if there are no files within the directory.
//If there are still files within the directory, return -1 and set osErrMsg toE_DIR_NOT_EMPTY. 
//If someone tries to remove the root directory ("/"), don't allow them to do it! Return -1 and set osErrMsg to E_DEL_ROOT_DIR.
int DirectoryAPI::Dir_Unlink(string path)
{

	//string h = path.c_str("\\");


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

int DirectoryAPI::getNumDirectories()
{
	return numDirectories;
}


//HELPER METHODS:

unique_ptr<DirectoryINode> DirectoryAPI::findDirectory(string path)
{
	unique_ptr<DirectoryINode> currentINode, returnINode;
	string delimiter = "/";
	string foundString;

	currentINode.reset(UMDLibOS::rootDirectory.get());
	
	//iterates through all DirectoryINodes until the desired directory INode is reached
	//possible valid input to consider:
	// "/a/a/"
	if (path[0] != '/')
		path = '/' + path;
	if (path[path.size() - 1] == '/')
		path = path.substr(0, path.size() - 1);
	while (path.find(delimiter) >= 0) 
	{
		foundString = path.substr(1, path.find(delimiter) - 1);
		path = path.substr(path.find(delimiter), path.size() - 1);
		for (int i = 0; i < currentINode->getNumberSubDirectories(); i++)
		{
			if (currentINode.get()->subDirectories[i]->getName() == foundString)
			{
				currentINode.reset(currentINode->subDirectories[i].get());
			}
			else
			{
				return NULL;
			}
		}
	}
	//handles the last directory name
	foundString = path.substr(1, path.size() - 1);
	for (int i = 0; i < currentINode->getNumberSubDirectories(); i++)
	{
		if (currentINode.get()->subDirectories[i]->getName() == foundString)
		{
			returnINode.reset(currentINode->subDirectories[i].get());
			return returnINode;
		}
	}
	return NULL;

}


