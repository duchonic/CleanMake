#include "source/serial.h"
#include "customLibs/helper.h"

#include "interface/IOperation.h"
#include "source/OperationFactory.h"

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
//static FT_HANDLE ftHandle[2];
//static uint8 buffer[SPI_DEVICE_BUFFER_SIZE] = { 0 };

//////////
/// Forward declaration Section
void mainProcedure();
void getNextMsg(periodic_info* info);
void setUp();

#define APP_CHECK_STATUS(exp) {if(exp!=FT_OK){printf("%s:%d:%s(): status(0x%x) \
!= FT_OK\n",__FILE__, __LINE__, __FUNCTION__,exp);exit(1);}else{;}};



int main() {

	DEBUG_LOG << "main entered" << '\n';

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
	(void)info;

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
