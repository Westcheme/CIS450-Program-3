#include "pch.h"
#include "CppUnitTest.h"
#include "UMDLibOS.h"
#include "DiskAPI.h"
#include "DirectoryAPI.h"
#include <cassert>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

DirectoryINode globalDirectoryINode;
DirectoryINode* globalDirectoryINodePointer;

namespace UMDLibOSUnitTest
{
	TEST_CLASS(UMDLibOSUnitTest)
	{
	public:
		
		//Test Method template
		TEST_METHOD(testMethodTemplate)
		{
			//arrange
			//act
			//assert
		}

		//Verify that disk boot returns 0 when no error
		TEST_METHOD(DISK_Init_NO_ERROR)
		{
			//arrange
			int expectedReturnCode = 0;
			int returnCode;

			//act
			returnCode = DiskAPI::Disk_Init();

			//assert
			Assert::AreEqual(expectedReturnCode, returnCode);

		}

		//Test Loading Disk doesn't give error code after initialization
		TEST_METHOD(Disk_Load_NO_ERROR)
		{
			//arrange
			int expectedReturnCode = 0;
			int returnCode;

			//act
			DiskAPI::Disk_Init();
			returnCode = DiskAPI::Disk_Load();

			//assert
			Assert::AreEqual(expectedReturnCode, returnCode);

		}

		//Verify that saving disk does not result in error after booting and loading
		TEST_METHOD(Disk_Save_NO_ERROR)
		{
			//arrange
			int expectedReturnCode = 0;
			int returnCode;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			returnCode = DiskAPI::Disk_Save();

			//assert
			Assert::AreEqual(expectedReturnCode, returnCode);
		}

		//Verify Disk_Write and Disk_Read work together
		TEST_METHOD(Disk_Read_Write_NO_ERROR)
		{
			//arrange
			int sectorNumber = 5;
			string content = "TestString";
			int contentLength = content.size();
			//writtenString must be same size as sector
			string writtenString = content.append(SECTOR_SIZE - contentLength, '0');
			string readString;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DiskAPI::Disk_Write(sectorNumber, writtenString);
			DiskAPI::Disk_Read(sectorNumber, readString);

			//assert
			Assert::AreEqual(writtenString, readString);
		}

		TEST_METHOD(Disk_Read_OUT_OF_BOUNDS)
		{
			//arrange
			int sectorNumber = 10000;
			int expectedReturn = -1;
			int actualReturn;
			string writtenString;
			string readString;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			actualReturn = DiskAPI::Disk_Read(sectorNumber, readString);

			//assert
			Assert::AreEqual(expectedReturn, actualReturn);
		}


		TEST_METHOD(Disk_Write_OUT_OF_BOUNDS)
		{
			//arrange
			int sectorNumber = 10000;
			int expectedReturn = -1;
			int actualReturn;
			string writtenString;
			string readString;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			actualReturn = DiskAPI::Disk_Write(sectorNumber, writtenString);

			//assert
			Assert::AreEqual(expectedReturn, actualReturn);
		}

		//Create a new directory in root
		//Verify directory exists, and that 
		//its name is same as input with a "/" at end
		TEST_METHOD(Create_Directory_From_Root)
		{
			//arrange
			string path = "/testDirectory";
			string expectedName = "testDirectory/";
			string foundName;
			int actualReturn, expectedReturn = 0;
			DirectoryINode* returnedDirectory = NULL;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			rootDirectory;
			actualReturn = DirectoryAPI::Dir_Create(path);
			if (expectedReturn != actualReturn) {
				foundName = "failed to create directory";
			}
			else
			{
				returnedDirectory = DirectoryAPI::findDirectory(path);
			}

			if (returnedDirectory == NULL) {
				foundName = "Directory created is NULL";
			}
			else
			{
				foundName = returnedDirectory->getName();
			}

			//assert
			Assert::AreEqual(expectedName, foundName);
		}

		//Test Method template
		TEST_METHOD(Dir_Create_In_Sub_Dir)
		{
			//arrange
			string parentPath = "/testDirectory";
			string subPath = parentPath + "/testSub";
			string expectedName = "testSub/";
			string foundName;
			int actualReturn, expectedReturn = 0;
			DirectoryINode* returnedDirectory = NULL;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DirectoryAPI::Dir_Create(parentPath);
			actualReturn = DirectoryAPI::Dir_Create(subPath);
			if (expectedReturn != actualReturn) {
				foundName = "failed to create directory";
			}
			else
			{
				returnedDirectory = DirectoryAPI::findDirectory(subPath);
			}

			if (returnedDirectory == NULL) {
				foundName = "Directory created is NULL";
			}
			else
			{
				foundName = returnedDirectory->getName();
			}

			//assert
			Assert::AreEqual(expectedName, foundName);
		}

		//Test Method template
		TEST_METHOD(Dir_Create_NAME_LENGTH_ERROR)
		{
			//arrange
			string expectedOSErrorMsg = "E_DIR_CREATE";

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DirectoryAPI::Dir_Create("ThisNameIs16Char");

			//assert
			Assert::AreEqual(expectedOSErrorMsg, UMDLibOS::getOSErrorMsg());

		}

		TEST_METHOD(Dir_Size_NO_ERROR_No_Files)
		{
			//arrange
			string parentPath = "/testDirectory";
			string subPath = parentPath + "/testSub";
			int actualReturn, expectedReturn = 0;
			DirectoryINode* returnedDirectory = NULL;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DirectoryAPI::Dir_Create(parentPath);
			DirectoryAPI::Dir_Create(subPath);
			actualReturn = DirectoryAPI::Dir_Size(subPath);

			//assert
			Assert::AreEqual(expectedReturn, actualReturn);
		}

		TEST_METHOD(Dir_Read_NO_ERROR_No_Files)
		{
			//arrange
			string parentPath = "/testDirectory";
			string subPath = parentPath + "/testSub";
			string expectedBufferContent = "testSub/00000000";
			string buffer;
			int actualReturn, expectedReturn = 0;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DirectoryAPI::Dir_Create(parentPath);
			DirectoryAPI::Dir_Create(subPath);
			actualReturn = DirectoryAPI::Dir_Read(parentPath, buffer, 20);

			//assert
			Assert::AreEqual(expectedBufferContent, buffer.substr(0, buffer.length()-4));
		}

		TEST_METHOD(Dir_Read_BUFFER_TOO_SMALL_No_Files)
		{
			//arrange
			string parentPath = "/testDirectory";
			string subPath = parentPath + "/testSub";
			string buffer;
			int actualReturn, expectedReturn = -1;
			DirectoryINode* returnedDirectory = NULL;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DirectoryAPI::Dir_Create(parentPath);
			DirectoryAPI::Dir_Create(subPath);
			actualReturn = DirectoryAPI::Dir_Read(parentPath, buffer, 0);

			//assert
			Assert::AreEqual(expectedReturn, actualReturn);
		}

		//Test Method template
		TEST_METHOD(Dir_Unlink_NO_ERROR)
		{
			//arrange
			string parentPath = "/testDirectory";
			string subPath = parentPath + "/testSub";
			DirectoryINode* returnedDirectory = NULL;

			//act
			DiskAPI::Disk_Init();
			DiskAPI::Disk_Load();
			DirectoryAPI::Dir_Create(parentPath);
			DirectoryAPI::Dir_Create(subPath);
			DirectoryAPI::Dir_Unlink(subPath);
			returnedDirectory = DirectoryAPI::findDirectory(subPath);

			//assert
			Assert::IsNull(returnedDirectory);
		}

		//Verify that decimal to hex conversion is correct
		TEST_METHOD(decimalToHex)
		{
			//arrange
			string expectedHex = "aa";
			int decimalInput = 170;
			string output = "";

			//act
			output = UMDLibOS::decimalToHex(decimalInput);
			
			//assert
			Assert::AreEqual(expectedHex, output);

		}

		//Verify that hex to decimal conversion is correct
		TEST_METHOD(hexToDecimal)
		{
			//arrange
			string hexInput = "0b";
			int expectedInt = 11;
			int output;

			//act
			output = UMDLibOS::hexToDecimal(hexInput);

			//assert
			Assert::AreEqual(expectedInt, output);
		}

		TEST_METHOD(DirectoryINode_Pounter_Assignment_Test)
		{
			//arrange
			DirectoryINode* initialINode;
			DirectoryINode* assignedINode;

			initialINode = new DirectoryINode;
			initialINode->setName("TestName");
			
			//act
			assignedINode = initialINode;

			//assert
			Assert::AreEqual(initialINode->getID(), assignedINode->getID());
		}

		TEST_METHOD(Global_DirectoryINode_Assignment_Test)
		{
			//arrange
			DirectoryINode* initialINode;
			DirectoryINode* assignedINode;

			initialINode = new DirectoryINode;
			initialINode->setName("TestName");
			globalDirectoryINode = *initialINode;

			//act
			assignedINode = &globalDirectoryINode;

			//assert
			Assert::AreEqual(initialINode->getID(), assignedINode->getID());
		}

		TEST_METHOD(Global_DirectoryINode_Pointer_Assignment_Test)
		{
			//arrange
			DirectoryINode* initialINode;
			DirectoryINode* assignedINode;

			initialINode = new DirectoryINode;
			initialINode->setName("TestName");
			globalDirectoryINodePointer = initialINode;

			//act
			assignedINode = globalDirectoryINodePointer;

			//assert
			Assert::AreEqual(initialINode->getID(), assignedINode->getID());
		}

		TEST_METHOD(string_find_substr_test)
		{
			//arrange
			string inputString = "/testDirectoryName";
			string delimiter = "/";
			int expectedReturnValue = -1;
			int actualReturnValue;

			//act
			actualReturnValue = inputString.find(delimiter);
			inputString = inputString.substr(actualReturnValue + 1, inputString.length() - actualReturnValue);
			actualReturnValue = inputString.find(delimiter);

			//assert
			Assert::AreEqual(expectedReturnValue, actualReturnValue);
		}

	};
}
