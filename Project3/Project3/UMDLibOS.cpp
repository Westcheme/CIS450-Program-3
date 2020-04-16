#include "UMDLibOS.h"

void UMDLibOS::inputSeekingLoop() {

	bool running = true;
	int integerResponse;
	string stringResponse;

	FileAccessAPI FA_API;
	FileSystemAPI FS_API;
	DirectoryAPI DIR_API;
	DiskAPI DISK_API;

	displayWelcomeMessage();
	//call FS_BOOT;

	while (running) {

		displaySystemState();
		displayUMDLibOSInteractions();

		cin >> integerResponse;

		switch (integerResponse) {
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			case 5:

				break;
			case 6:

				break;
			case 7:

				break;
			case 8:

				break;
			case 9:

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
string getOSErrorMsg()
{
	return osErrMsg;
}

void setDiskErrorMsg(string _diskErrMsg)
{
	diskErrMsg = _diskErrMsg;
}

void setOSErrorMsg(string _osErrMsg)
{
	osErrMsg = _osErrMsg;
}

////UTILITY METHODS BELOW

void print(string _message) {
	cout << _message;
}

void println(string _message) {
	cout << _message << "/n'";
}

void displayWelcomeMessage() {
	println("Welcome to UMDLibOS!");
	println("In this program, you will be interacting with UMDLibOS");
	println("Please enter an integer from the list below");

}

void displaySystemState() {
	println("CURRENT SYSTEM STATE:");
	//if osErrMsg is not null or empty display notification error message exists
	//if diskErrMsg is not null or empty display notification error message exists
	//Show current file
	//Show open files
}

void displayUMDLibOSInteractions() {
	println("1. Create File");
	println("2. Open File");
	println("3. Read File");
	println("4. Write File");
	println("5. Seek File");
	println("6. Close File");
	println("7. Unlink File");
	println("8. Check OS Error Message");
	println("9. Check Disk Error Message");
}