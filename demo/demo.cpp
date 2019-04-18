#include "serial.h"
#include "logger.h"
#include "xmlEventParser.h"
#include "customLibs/helper.h"

#include "interface/IOperation.h"
#include "OperationFactory.h"

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

//////////
/// Forward declaration Section
void mainProcedure();
void getNextMsg(periodic_info* info);
void setUp();

int main() {

	DEBUG_LOG << "main entered" << '\n';
	struct periodic_info info;

	Logger myLogger;
	Serial mySerial;
	Helper myHelper;

#ifdef IS_MAC
	sleep(1);
#elif IS_LINUX
	sleep(1);
#elif IS_VISUAL_STUDIO
	::_sleep(1000);
#else
  Sleep(1000);
#endif

	setUp();

	#ifdef IS_MAC
		sleep(1);
	#elif IS_LINUX
		sleep(1);
	#elif IS_VISUAL_STUDIO
		::_sleep(1000);
	#else
	  Sleep(1000);
	#endif

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
#ifdef IS_MAC
		sleep(1);
#elif IS_LINUX
		sleep(1);
#elif IS_VISUAL_STUDIO
		::_sleep(1000);
#else
		Sleep(1000);
#endif
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
				IMessage* pMessage = pOperation->getMessage();

				//INFO_LOG << "message: " << pMessage->toString() << '\n';
				
				//IMessageProcessor* processor = MessageProcessorFactory::getMessageProcessor();
				//processor->processMessage(pMessage);
			}
		}
		catch (std::exception & ex) {
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
