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


static void thread_with_delay(int delay){
    for (int runs=0; runs<10; runs++) {
        this_thread::sleep_for(1s * delay);
        INFO_LOG << "hello michael from thread, run: " << runs << '\n';
        this_thread::sleep_for(1s * delay);
        INFO_LOG << "byby" << '\n';
    }
}


int main() {

	DEBUG_LOG << "main entered" << '\n';
	struct periodic_info info;

    using millis = chrono::duration<int, ratio<1, 1000>>;
    using fortnight = chrono::duration<float, ratio<14*24*60*60, 1>>;
    using hour = chrono::duration<float, ratio<60*60,1>>;

    chrono::seconds sec(1);
    chrono::minutes min(66);

    INFO_LOG << thread::hardware_concurrency() << " current threads supported" << '\n';

    DEBUG_LOG << "1 SEC IS: " << millis(sec).count() << "ms" << '\n';
    DEBUG_LOG << "1 SEC IS: " << chrono::milliseconds(sec).count() << "ms" << '\n';
    DEBUG_LOG << "66min : " << millis(min).count() << "ms" << '\n';
    DEBUG_LOG << "66min : " << chrono::duration_cast<chrono::hours>(min).count() << "hour" << '\n';
    DEBUG_LOG << "66min : " << hour(min).count() << "hour" << '\n';
    DEBUG_LOG << "66min : " << fortnight(min).count() << "fortnight" << '\n';

    thread th_nummerOne {
        thread_with_delay, 1
    };

    th_nummerOne.detach();

	Serial mySerial;
	Helper myHelper;

#ifdef IS_MAC
	sleep(1);
#elif IS_LINUX
	sleep(1);
#elif IS_VISUAL_STUDIO
	Sleep(1000);
#else
  Sleep(1000);
#endif

	setUp();

	#ifdef IS_MAC
		sleep(1);
	#elif IS_LINUX
		sleep(1);
	#elif IS_VISUAL_STUDIO
		Sleep(1000);
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
		Sleep(1000);
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
