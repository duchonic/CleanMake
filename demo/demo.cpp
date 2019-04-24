#include "serial.h"
#include "xmlEventParser.h"
#include "customLibs/helper.h"

#include "interface/IOperation.h"
#include "OperationFactory.h"

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

//////////
/// Forward declaration Section
void mainProcedure();
void getNextMsg(periodic_info* info);
void setUp();

int main() {

	DEBUG_LOG << "main entered" << '\n';

	Init_libMPSSE();

	FT_STATUS status_spi = FT_OK;
	uint32 noChannels_spi = 0;
	status_spi = SPI_GetNumChannels(&noChannels_spi);
	DEBUG_LOG << "status mpsse_spi: " << status_spi << '\n';

	FT_STATUS status_i2c = FT_OK;
	uint32 noChannels_i2c = 0;
	status_i2c = I2C_GetNumChannels(&noChannels_i2c);
	DEBUG_LOG << "status mpsse_i2c: " << status_i2c << '\n';

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

			if (pOperation->hasMessageArrived()) {
				IMessage* pMessage = pOperation->getMessage();

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
