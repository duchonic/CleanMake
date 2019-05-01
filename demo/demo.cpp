#include "serial.h"
#include "xmlEventParser.h"
#include "customLibs/helper.h"

#include "interface/IOperation.h"
#include "OperationFactory.h"

#include <functional>
#include <thread>
#include <chrono>
#include <ratio>

using namespace std;
using namespace chrono_literals;

#ifdef IS_MAC
	#include <unistd.h>
#elif IS_LINUX
	#include <unistd.h>
#else
	#include <windows.h>
#endif
#include <libMPSSE_spi.h>
#include <libMPSSE_i2c.h>


struct periodic_info
{
	int timer_fd;
	unsigned long long wakeups_missed;
};

//////////
/// Global Variable Section
volatile bool bAbort = false;

/* Application specific macro definations */
#define SPI_DEVICE_BUFFER_SIZE		256


#define CHANNEL_TO_OPEN			0	/*0 for first available channel, 1 for next... */


/******************************************************************************/
/*		Global variables */
/******************************************************************************/
static FT_HANDLE ftHandle[2];
static uint8 buffer[SPI_DEVICE_BUFFER_SIZE] = { 0 };

//////////
/// Forward declaration Section
void mainProcedure();
void getNextMsg(periodic_info* info);
void setUp();

#define APP_CHECK_STATUS(exp) {if(exp!=FT_OK){printf("%s:%d:%s(): status(0x%x) \
!= FT_OK\n",__FILE__, __LINE__, __FUNCTION__,exp);exit(1);}else{;}};

void th_mpsseTest(void) {

	FT_STATUS status = FT_OK;
	FT_DEVICE_LIST_INFO_NODE devList = { 0 };
	ChannelConfig channelConf = { 0 };
	uint8 address = 0;
	uint32 channels = 0;
	uint16 data = 0;
	uint8 i = 0;
	uint8 latency = 255;

	channelConf.ClockRate = 5000;
	channelConf.LatencyTimer = latency;
	channelConf.configOptions = SPI_CONFIG_OPTION_MODE0 | SPI_CONFIG_OPTION_CS_DBUS3;// | SPI_CONFIG_OPTION_CS_ACTIVELOW;
	channelConf.Pin = 0x00000000;/*FinalVal-FinalDir-InitVal-InitDir (for dir 0=in, 1=out)*/


		/* init library */
#ifdef _MSC_VER
	Init_libMPSSE();
#endif
	status = SPI_GetNumChannels(&channels);
	APP_CHECK_STATUS(status);
	printf("Number of available SPI channels = %d\n", (int)channels);

	if (channels > 0)
	{
		for (i = 0; i < channels; i++)
		{
			status = SPI_GetChannelInfo(i, &devList);
			APP_CHECK_STATUS(status);
			printf("Information on channel number %d:\n", i);
			/* print the dev info */
			printf("		Flags=0x%x\n", devList.Flags);
			printf("		Type=0x%x\n", devList.Type);
			printf("		ID=0x%x\n", devList.ID);
			printf("		LocId=0x%x\n", devList.LocId);
			printf("		SerialNumber=%s\n", devList.SerialNumber);
			printf("		Description=%s\n", devList.Description);
			printf("		ftHandle=0x%x\n", (unsigned int)devList.ftHandle);/*is 0 unless open*/
		}

		/* Open the first available channel */
		status = SPI_OpenChannel(0, &ftHandle[0]);
		APP_CHECK_STATUS(status);
		printf("\nhandle=0x%x status=0x%x\n", (unsigned int)ftHandle[0], status);
		status = SPI_InitChannel(ftHandle[0], &channelConf);


		/* Open the first available channel */
		status = I2C_OpenChannel(1, &ftHandle[1]);
		APP_CHECK_STATUS(status);
		printf("\nhandle=0x%x status=0x%x\n", (unsigned int)ftHandle[1], status);
		status = I2C_InitChannel(ftHandle[1], &channelConf);

		APP_CHECK_STATUS(status);
	}

	while (true){
		FT_WriteGPIO(ftHandle[0], 0b10000001, 0b00000000);
		FT_WriteGPIO(ftHandle[1], 0b00000101, 0b00000000);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		FT_WriteGPIO(ftHandle[0], 0b10000001, 0b10000001);
		FT_WriteGPIO(ftHandle[1], 0b00000101, 0b00000101);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

int main() {

	DEBUG_LOG << "main entered" << '\n';

	std::thread t1(th_mpsseTest);
	t1.detach();

	Cleanup_libMPSSE();

	struct periodic_info info;


	Serial mySerial;
	Helper myHelper;

	setUp();

	SLEEP_ms(1000);

	mySerial.write("\n mainloop start");
	while (!bAbort) {
		getNextMsg(&info);
		mySerial.write(".");
	}

	return 0;
}


// Set up and initialize
void setUp() {
	DEBUG_LOG << "setup started" << std::endl;
	// initialize operation (dispatcher)
	OperationFactory::getOperation()->initDriver();
}


// Check and receive (timer) message
void getNextMsg(periodic_info* info) {
	// Run all stuff
	//if (PeriodicCycle::getInstance()->isPeriodicCycleEnabled()) {
	if (true) {
		mainProcedure();
		SLEEP_ms(29);
	}
}

// The main procedure
void mainProcedure() {
	IOperation* pOperation = OperationFactory::getOperation();

	INFO_LOG << "main loop running..." << '\n';

	try {
		// process operation
		pOperation->runDriver();

		try {

#ifdef IS_MAC

#elif IS_LINUX

#else

#endif
			if (pOperation->hasMessageArrived()) {
				//IMessage* pMessage = pOperation->getMessage();

				//INFO_LOG << "message: " << pMessage->toString() << '\n';

				//IMessageProcessor* processor = MessageProcessorFactory::getMessageProcessor();
				//processor->processMessage(pMessage);
			}
		}
		catch (...) {
			ERROR_LOG << "Exception in main Procedure" << '\n';
		}

	}
	catch (...) { // here, we are not able to communicate with SYS
		ERROR_LOG << "Unhandled exception in SYS-Operation occured. GSM1101 device is going to restart now..." << '\n';
		bAbort = true;
		return;
	}

	// Drive the drivers
	try {
		//ControllerDriverManager::getInstance()->runDrivers();
	}
	catch (...) {
		ERROR_LOG << "Unhandled exception in SYS" << '\n';
		bAbort = true; //terminates application
		return;
	}

}
