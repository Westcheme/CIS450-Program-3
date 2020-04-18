#include "pch.h"
#include "CppUnitTest.h"
#include "UMDLibOS.h"
#include "DiskAPI.h"
#include "DirectoryAPI.h"
#include <cassert>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

	};
}
