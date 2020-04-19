#pragma once
#include "INode.h"
#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

#define MAX_FILES_AND_DIRECTORIES 100
#define NUM_SECTORS 1000

#pragma once

class DirectoryAPI;
class DiskAPI;
class FileAccessAPI;
class FileSystemAPI;

static string osErrMsg;
static string diskErrMsg;
static bool fs_available;
static FileAccessAPI* FA_API;
static FileSystemAPI* FS_API;
static bool DiskSectorBitmap[NUM_SECTORS];
static bool INodeBitmap[NUM_SECTORS];
static DirectoryINode rootDirectory;

class UMDLibOS
{
private:
	static void print(string message);
	static void println(string message);
	static void displayWelcomeMessage();
	static void displaySystemState();
	static void displayUMDLibOSInteractions();
public:
	UMDLibOS();
	static void inputSeekingLoop();
	static string getDiskErrorMsg();
	static string getOSErrorMsg();
	static void setDiskErrorMsg(string _diskErrMsg);
	static void setOSErrorMsg(string _osErrMsg);
	static bool fileSystemAccessible();
	static int hexToDecimal(string hex);
	static string decimalToHex(int decimal);
};
