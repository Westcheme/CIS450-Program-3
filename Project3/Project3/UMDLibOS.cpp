#include "UMDLibOS.h"
#include "DiskAPI.h"
#include "FileAccessAPI.h"
#include "FileSystemAPI.h"

UMDLibOS::UMDLibOS()
{
	osErrMsg = "";
	diskErrMsg = "";
	FS_API = new FileSystemAPI;
	FA_API = new FileAccessAPI;
	fs_available = false;
	for (int i = 0; i < NUM_SECTORS; i++)
	{
		DiskSectorBitmap[i] = 0;
	}
}

void UMDLibOS::inputSeekingLoop() {

	bool running = true;
	int integerResponse;
	string stringResponse;

	string buffer;
	int size;

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
				FA_API->File_Create(stringResponse);
				break;
			case 2:
				cout << "Enter the directory and file name: ";
				cin >> stringResponse;
				FA_API->File_Open(stringResponse);
				break;
			case 3:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				cout << "Enter a size: ";
				cin >> size;
				FA_API->File_Read(integerResponse, buffer, size);
				break;
			case 4:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				cout << "Enter a size: ";
				cin >> size;
				FA_API->File_Write(integerResponse, buffer, size);
				break;
			case 5:
				int offset;
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				cout << "Choose an offset: ";
				cin >> offset;
				FA_API->File_Seek(integerResponse, offset);
				break;
			case 6:
				FA_API->showOpenFiles();
				cout << "Choose a file: ";
				cin >> integerResponse;
				FA_API->File_Close(integerResponse);
				break;
			case 7:
				cout << "Enter the directory and file name: ";
				cin >> stringResponse;
				FA_API->File_Unlink(stringResponse);
				break;
			case 8:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				DR_API->Dir_Create(stringResponse);
				break;
			case 9:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				DR_API->Dir_Size(stringResponse);
				break;
			case 10:
				string buffer;
				int size;
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				cout << "Enter a size: ";
				cin >> size;
				DR_API->Dir_Read(stringResponse, buffer, size);
				break;
			case 11:
				cout << "Enter the directory and name: ";
				cin >> stringResponse;
				DR_API->Dir_Unlink(stringResponse);
				break;
			case 12:
				cout << getOSErrorMsg();
				break;
			case 13:
				cout << getDiskErrorMsg();
				break;
			case 14:
				FS_API->FS_Boot();
				break;
			case 15:
				FS_API->FS_Sync();
				break;
			case 16:
				FS_API->FS_Reset();
				break;
			case 17:

				break;
			default:
				println("Invalid integer entered. Please try again.");
				cin >> stringResponse;
				continue;
		}
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
	println("OS Error:" + osErrMsg);
	println("Disk Error:" + diskErrMsg);
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