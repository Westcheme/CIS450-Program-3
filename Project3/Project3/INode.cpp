#include "INode.h"


INode::INode()
{
	size = 0;
}

FileINode::FileINode()
{
	fileType = "File";
}

DirectoryINode::DirectoryINode()
{
	fileType = "Directory";
	subDirectories = NULL;
	subFiles = NULL;
}


void INode::setName(string _name)
{
	name = _name;
}