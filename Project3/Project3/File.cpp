#include "File.h"


File::File()
{
	Root->name = "Root";
	Root->fd = 0;
}

void File::setName(string _name)
{
	name = _name;
}

void File::setFD(int _fd)
{
	fd = _fd;
}
