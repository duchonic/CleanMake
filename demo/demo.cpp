#include "serial.h"
#include "logger.h"
#include "xmlEventParser.h"
#include "customLibs/helper.h"

#include "interface/IOperation.h"
#include "OperationFactory.h"

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

	setUp();

	while (!bAbort) {
		getNextMsg(&info);
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
		::_sleep(1000);
	}
}

// The main procedure
void mainProcedure() {

	IOperation* pOperation = OperationFactory::getOperation();

	try {
		// process operation
		pOperation->runDriver();

		try {

			std::string xmlMessage{ "<xml><item>dkdk</item></xml>" };
			DEBUG_LOG << xmlMessage << '\n';
			XMLEventParser parser(xmlMessage.c_str());

			if (pOperation->hasMessageArrived()) {
			//	IMessage* pMessage = pOperation->getMessage();
			//	IMessageProcessor* processor = MessageProcessorFactory::getMessageProcessor();
			//	
			//	processor->processMessage(pMessage);
				INFO_LOG << "msg arrived" << '\n';
			}
			else {
				INFO_LOG << "NO MESSAGE" << '\n';
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