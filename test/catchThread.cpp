// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include <thread>
#include "helper.h"
#include <ctime>          // std::time_t, std::tm, std::localtime, std::mktime
#include <chrono>         // std::chrono::system_clock
#include <iomanip>        // std::put_time
#include <cstdlib>

#include "TimeUtil.h"
#include "Timer.h"


static const int MAIN_CYCLE_TIME_ms = 20;

static bool g_closeThread = false;
static bool isLastTrigger = false;

static bool setLastTrigger = false;

void driveThread(bool *hasAck_p) {
	g_closeThread = false;
	while (!*hasAck_p) {
		INFO_LOG << "thread running... (leds are blinking)" << std::endl;
		if (g_closeThread) {
			INFO_LOG << "close thread" << std::endl;
			break;
		}
		*hasAck_p = setLastTrigger;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	if (*hasAck_p) {
		INFO_LOG << "hasAck" << std::endl;
	}
}

TEST_CASE("thread (join) tests waiting for input of user") {
	INFO_LOG << "some thread (join) tests" << std::endl;

	g_closeThread = false;
	std::thread testThread(driveThread, &isLastTrigger);

	SLEEP_ms(2500);
	g_closeThread = true;
	//setLastTrigger = true;
	testThread.join();
}

TEST_CASE("thread (detach) tests waiting for input of user") {
	INFO_LOG << "some thread (detach) tests" << std::endl;
	//std::thread testThread(driveThread, 500);
	//testThread.detach();
	//INFO_LOG ( "press enter to abort test! " );
	//std::string line;
	//std::getline(std::cin, line);

	SLEEP_ms(2500);

	
}


void sleepUntilNextMinuteThread(void) {
	INFO_LOG << "thread sleep until started" << std::endl;
	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());

	struct std::tm* ptm = std::localtime(&tt);
	INFO_LOG << "Current time: " << std::put_time(ptm, "%X") << std::endl;

	INFO_LOG << "Waiting for the next minute to begin..." << std::endl;
	++ptm->tm_min; ptm->tm_sec = 0;
	std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

	INFO_LOG << std::put_time(ptm, "%X") << " reached!" << std::endl;
}

TEST_CASE("sleep until next minute") {
	//std::thread sleepUntil(sleepUntilNextMinuteThread);
	//sleepUntil.join();
}

auto startTime = std::chrono::high_resolution_clock::now();

int getSlot(void) {
	auto nowTime = std::chrono::steady_clock::now();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime
		- startTime).count();
	return ((millis % 100) / MAIN_CYCLE_TIME_ms);
}

void sleepUntilNextSlot(void) {
	auto nowTime = std::chrono::steady_clock::now();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime
		- startTime).count() % MAIN_CYCLE_TIME_ms;
	std::this_thread::sleep_until(std::chrono::steady_clock::now()
		- std::chrono::milliseconds(millis)
		+ std::chrono::milliseconds(MAIN_CYCLE_TIME_ms));
}

static const int CATCHTESTDELAY_ms = MAIN_CYCLE_TIME_ms;
static const int RUNS = 50;

void simulateMainProcedure(void) {
	SLEEP_ms((std::rand() % (CATCHTESTDELAY_ms * 2)) + 1);
}

void printOutLoops(void) {
	static std::chrono::steady_clock::time_point loopCountLast;
	static int loops = 0;

	if ((loops++ % 50) == 0) {
		INFO_LOG << "50 loops (1sec) in: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
				- loopCountLast).count() << "ms" << std::endl;
		loopCountLast = std::chrono::steady_clock::now();
	}
}

TEST_CASE( "sleep (until) next CATCHTESTDELAY_ms (if slotStart == slotEnd)" ) {
	int minProcent = 100;
	int maxProcent = 0;
	int totalWarnings = 0;

	for (int runs = RUNS; runs > 0; runs--) {
		auto slotStart = getSlot();

		/** simulate the mainProcedure() */
		simulateMainProcedure();
		/** end of the simulate mainProcedure() */

		/* only sleep until next slot if current process was within the same slot
		   if precess was longer than a slot period, start with the next one */
		if (slotStart == getSlot()) {
			sleepUntilNextSlot();
		}

		printOutLoops();
	}
	INFO_LOG << "totalWarnings: " << totalWarnings << " min: " << minProcent << " max: " << maxProcent << std::endl;

}


TEST_CASE("sleep (until) next CATCHTESTDELAY_ms") {
	int minProcent = 100;
	int maxProcent = 0;
	int totalWarnings = 0;
	std::chrono::steady_clock::time_point loopCountLast;
	int loops = 0;

	for (int runs = RUNS; runs > 0; runs--) {
		auto slotStart = getSlot();

		/** simulate the mainProcedure() */
		simulateMainProcedure();
		/** end of the simulate mainProcedure() */

		sleepUntilNextSlot();
		printOutLoops();
	}
	INFO_LOG << "totalWarnings: " << totalWarnings << " min: " << minProcent << " max: " << maxProcent << std::endl;

}
