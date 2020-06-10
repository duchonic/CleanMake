// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "sleep.h"
#include <ftd2xx/ftd2xx.h>
#include <vector>


FT_STATUS ftStatus;
static FT_HANDLE heaterHandle;
static FT_HANDLE filterHandle;
static FT_HANDLE synchHandle;


void setupFilterHandle(void) {

	ftStatus = FT_SetBaudRate(filterHandle, FT_BAUD_115200);
	REQUIRE(ftStatus == FT_OK);

	ftStatus = FT_SetDataCharacteristics(filterHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
	REQUIRE(ftStatus == FT_OK);

	ftStatus = FT_SetFlowControl(filterHandle, FT_FLOW_NONE, NULL, NULL);
	REQUIRE(ftStatus == FT_OK);

	ftStatus = FT_SetTimeouts(filterHandle, 500, 1000);
	REQUIRE(ftStatus == FT_OK);

	ftStatus = FT_SetBreakOff(filterHandle);
	REQUIRE(ftStatus == FT_OK);

	SLEEP_ms(300);
	ftStatus = FT_ResetPort(filterHandle);
	REQUIRE(ftStatus == FT_OK);

	SLEEP_ms(300);
}


void sendOpCode(char *opCode_p) {
	DWORD bytesWritten = 0;
	ftStatus = FT_Write(filterHandle, opCode_p, 1, &bytesWritten);
	REQUIRE(ftStatus == FT_OK);
	REQUIRE(bytesWritten == 1);
}

void getAck(void) {
	char* pBuffer{};
	DWORD txBytes = 0;
	DWORD rxBytes = 0;
	DWORD eventStatus = 0;
	DWORD readBytes = 0;

	while (rxBytes == 0) {
		FT_GetStatus(filterHandle, &rxBytes, &txBytes, &eventStatus);
		REQUIRE(ftStatus == FT_OK);
		SLEEP_ms(100);
		INFO_LOG("rxBytes:" << rxBytes << " txBytes:" << txBytes);
		// always call FT_GetStatus before FT_Read or else FT_Read will not work properly
	}

	ftStatus = FT_Read(filterHandle, pBuffer, 1, &readBytes);
	REQUIRE(ftStatus == FT_OK);
	REQUIRE(pBuffer[0] == 0x4f);
}

void getNull(void) {
	char* pBuffer{};
	DWORD txBytes = 0;
	DWORD rxBytes = 0;
	DWORD eventStatus = 0;
	DWORD readBytes = 0;

	while (rxBytes == 0) {
		FT_GetStatus(filterHandle, &rxBytes, &txBytes, &eventStatus);
		REQUIRE(ftStatus == FT_OK);
		SLEEP_ms(100);
		INFO_LOG("rxBytes:" << rxBytes << " txBytes:" << txBytes);
		// always call FT_GetStatus before FT_Read or else FT_Read will not work properly
	}

	ftStatus = FT_Read(filterHandle, pBuffer, 1, &readBytes);
	REQUIRE(ftStatus == FT_OK);
	REQUIRE(pBuffer[0] == 0x00);
}

void sendLen(char *len_p) {
	DWORD bytesWritten = 0;
	ftStatus = FT_Write(filterHandle, len_p, 1, &bytesWritten);
	REQUIRE(ftStatus == FT_OK);
	REQUIRE(bytesWritten == 1);
}

void sendData(char *data_p, DWORD len) {
	DWORD bytesWritten = 0;
	ftStatus = FT_Write(filterHandle, data_p, len, &bytesWritten);
	REQUIRE(ftStatus == FT_OK);
	REQUIRE(bytesWritten == len);
}

SCENARIO("ftd2xx ") {
	INFO_LOG("check the ftd2xx api");
}

SCENARIO("list devices") {
	DWORD numDevs;

	ftStatus = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);

	INFO_LOG("Available Devices: " << numDevs);

	for (int idx = 0; idx < numDevs; idx++) {
		FT_HANDLE ftHandleForListDetails;
		FT_DEVICE ftDeviceForListDetails;
		DWORD deviceID;
		char SerialNumber[16];
		char Description[64];

		ftStatus = FT_Open(idx, &ftHandleForListDetails);
		if (ftStatus == FT_OK) {

			ftStatus = FT_GetDeviceInfo(ftHandleForListDetails,
				&ftDeviceForListDetails, &deviceID, SerialNumber,
				Description, NULL);

			REQUIRE(ftStatus == FT_OK);

			DEBUG_LOG("sn:" << SerialNumber << " desc:" << Description);

			if (SerialNumber[8] == 'A') {
				INFO_LOG(Description << " > save to heaterHandle");
				heaterHandle = ftHandleForListDetails;
			}
			else if (SerialNumber[8] == 'B') {
				INFO_LOG(Description << " > save to filterHandle");
				filterHandle = ftHandleForListDetails;
			}
			else if (SerialNumber[8] == 'C') {
				INFO_LOG(Description << " > save to synchHandle");
			}
			else if (SerialNumber[8] == 'D') {
				INFO_LOG(Description << " > Reserve found");
			}
			else if (SerialNumber[7] == 'H') {
				INFO_LOG(Description << " > Testbox found");
			}
			else {
				INFO_LOG(Description << " no handle");
			}

		}
	}

	REQUIRE(heaterHandle != NULL);
	REQUIRE(filterHandle != NULL);

	setupFilterHandle();
	sendOpCode((char *)0x11);
	getAck();
	sendLen( (char *)0x03);
	char data[] = { 0x40, 0x60, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x39, 0xf8 };
	sendData( (char *)data, 10);
	getAck();
	
	//getNull();
}


//SCENARIO("communication to filterwheel") {
//	DWORD readBytes = 0;
//	DWORD txBytes = 0;
//	DWORD rxBytes = 0;
//	DWORD eventStatus = 0;
//	DWORD bytesWritten = 0;
//
//	char* pBuffer{};
//	char ok = 0x4f;
//	char c;
//
//
//		
//
//
//
//
//
//	pBuffer = &ok;
//	ftStatus = FT_Write(filterHandle, pBuffer, 1, &bytesWritten);
//	REQUIRE(ftStatus == FT_OK);
//	REQUIRE(bytesWritten == 1);
//
//
//	rxBytes = 0;
//	while (rxBytes < 7) {
//		FT_GetStatus(filterHandle, &rxBytes, &txBytes, &eventStatus);
//		REQUIRE(ftStatus == FT_OK);
//		SLEEP_ms(100);
//		INFO_LOG("rxBytes:" << rxBytes << " txBytes:" << txBytes);
//		// always call FT_GetStatus before FT_Read or else FT_Read will not work properly
//	}
//
//	ftStatus = FT_Read(filterHandle, pBuffer, 7, &readBytes);
//	REQUIRE(ftStatus == FT_OK);
//	REQUIRE(readBytes == 7);
//		
//
//	pBuffer = &ok;
//	ftStatus = FT_Write(filterHandle, pBuffer, 1, &bytesWritten);
//	REQUIRE(ftStatus == FT_OK);
//	REQUIRE(bytesWritten == 1);
//
//}

