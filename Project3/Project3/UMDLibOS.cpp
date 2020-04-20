#include "UMDLibOS.h"
#include "DiskAPI.h"
#include "FileAccessAPI.h"
#include "FileSystemAPI.h"
#include "stdlib.h"

UMDLibOS::UMDLibOS()
{
	osErrMsg = "";
	diskErrMsg = "";
	FS_API = new FileSystemAPI();
	FA_API = new FileAccessAPI();
	fs_available = false;
	for (int i = 0; i < NUM_SECTORS; i++)
	{
		DiskSectorBitmap[i] = 0;
	}
}

void UMDLibOS::inputSeekingLoop() {

	string buffer = "";
	int size = -1;
	int offset = -1;
	bool running = true;
	int integerResponse;
	string stringResponse;

	displayWelcomeMessage();

	//askLoadExternalDisk(); //Loads an external disk from a file and writes it to externalDisk

	//call FS_Boot exactly once;
	FS_API->FS_Boot();

	while (running) {

		displaySystemState();
		displayUMDLibOSInteractions();

		cin >> integerResponse;

		switch (integerResponse) {
			case 1:
				cout << "Enter the directory and file name: ";
				cin >> stringResponse;
				if (FA_API->File_Create(stringResponse) == -1)
					cout << "Error calling File_Create.";
				break;
			case 2:
				cout << "Enter the directory and file name: ";
				cin >> stringResponse;
				if (-1 == FA_API->File_Open(stringResponse))
					cout << "Error calling File_Open";
				break;
			case 3:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				cout << "Enter a size: ";
				cin >> size;
				if (-1 == FA_API->File_Read(integerResponse, buffer, size))
					cout << "Error calling File_Read";
				cout << "Buffer Contents: \n" << buffer;
				break;
			case 4:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				cout << "Enter a size: ";
				cin >> size;
				cout << "Enter the contents of the file.";
				cin >> buffer;
				if (-1 == FA_API->File_Write(integerResponse, buffer, size))
					cout << "Error calling File_Write";
				break;
			case 5:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				cout << "Choose an offset: ";
				cin >> offset;
				if (-1 == FA_API->File_Seek(integerResponse, offset))
					cout << "Error calling File_Seek";
				else
					cout << "File pointer set.";
				break;
			case 6:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				if (-1 == FA_API->File_Close(integerResponse))
					cout << "Error calling File_Close";
				break;
			case 7:
				cout << "Enter the directory and file name: ";
				cin >> stringResponse;
				if (-1 == FA_API->File_Unlink(stringResponse))
					cout << "Error calling File_Unlink";
				break;
			case 8:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				if (-1 == DR_API->Dir_Create(stringResponse))
					cout << "Error calling Dir_Create";
				break;
			case 9:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				if (-1 == (size = DR_API->Dir_Size(stringResponse)))
					cout << "Error calling Dir_Size";
				else
					cout << "Size is " << size;
				break;
			case 10:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				cout << "Enter a size: ";
				cin >> size;
				if (-1 == (DR_API->Dir_Read(stringResponse, buffer, size)))
					cout << "Error calling Dir_Read";
				cout << "Buffer contents\n" << buffer;
				break;
			case 11:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				if (-1 == (DR_API->Dir_Unlink(stringResponse)))
					cout << "Error in Dir_Unlink";
				break;
			case 12:
				cout << getOSErrorMsg();
				break;
			case 13:
				cout << getDiskErrorMsg();
				break;
			case 14:
				if (-1 == (FS_API->FS_Boot()))
					cout << "Error calling FS_Boot";
				break;
			case 15:
				if (-1 == (FS_API->FS_Sync()))
					cout << "Error calling FS_Sync";
				break;
			case 16:
				if (-1 == (FS_API->FS_Reset()))
					cout << "Error calling FS_Reset";
				break;
			case 17:
				osErrMsg = "";
				diskErrMsg = "";
				break;
			default:
				println("Invalid integer entered. Please try again.");
				continue;
		}

		//cout << "Press enter to continue";
		system("pause");

		system("cls");

	}

}

string UMDLibOS::getDiskErrorMsg()
{
	return diskErrMsg;
}
string UMDLibOS::getOSErrorMsg()
{
	return osErrMsg;
}

void UMDLibOS::setDiskErrorMsg(string _diskErrMsg)
{
	diskErrMsg = _diskErrMsg;
}

void UMDLibOS::setOSErrorMsg(string _osErrMsg)
{
	osErrMsg = _osErrMsg;
}

bool UMDLibOS::fileSystemAccessible()
{
	return fs_available;
}

int UMDLibOS::hexToDecimal(string hex)
{
	int decimal;
	stringstream ss;
	ss << hex; // std::string hex_value
	ss >> std::hex >> decimal; //int decimal_value
	return decimal;
}

string UMDLibOS::decimalToHex(int decimal)
{
	stringstream ss;
	ss << std::hex << decimal; // int decimal_value
	string res(ss.str());
	return res;
}

////UTILITY METHODS BELOW

void UMDLibOS::print(string _message) {
	cout << _message;
}

void UMDLibOS::println(string _message) {
	cout << _message << "\n'";
}

void UMDLibOS::displayWelcomeMessage() {
	println("Welcome to UMDLibOS!");
	println("In this program, you will be interacting with UMDLibOS");
	println("Please enter an integer from the list below");

}

void UMDLibOS::displaySystemState() {
	println("CURRENT SYSTEM STATE:");
	println("OS Error: " + osErrMsg);
	println("Disk Error: " + diskErrMsg);
	//if osErrMsg is not null or empty display notification error message exists
	//if diskErrMsg is not null or empty display notification error message exists
	//Show current file
	//Show open files
}

void UMDLibOS::displayUMDLibOSInteractions() {
	println("1. Create File");
	println("2. Open File");
	println("3. Read File");
	println("4. Write File");
	println("5. Seek File");
	println("6. Close File");
	println("7. Unlink File");
	println("8. Create Directory");
	println("9. Size Directory");
	println("10. Read Directory");
	println("11. Unlink Directory");
	println("12. Check OS Error Message");
	println("13. Check Disk Error Message");
	println("14. Call FS_Boot()");
	println("15. Call FS_Sync()");
	println("16. Call FS_Reset()");
	println("17. Clear Error Messages");
}