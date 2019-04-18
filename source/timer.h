#pragma once

#include <time.h>
#include "source/timeUtil.h"

#include <map>
#include <string>
#include <stdexcept>


class Timer {

public:

	enum {
		MAIN_CYCLE_TIME = 20,		// [ms]
		KEYBOARD_CYCLE_TIME = 1000, // [ms]
	};

	// start new timer
	static void startTimer(const std::string& timerID, unsigned int timeMilliSeconds);

	// restart timer with the same timeout
	static void restartTimer(const std::string& timerID);

	// check if timer is set
	static bool isTimerSet(const std::string& timerID);

	// check if time is reached
	static bool timeReached(const std::string& timerID);

	// get the elapsed time since the timer was started
	static int getTime(const std::string& timerID);
	static int getTimeUs(const std::string& timerID);

	// remove timer
	static void removeTimer(const std::string& timerID);

private:

	// The timer values
	struct TIMER_VALUES {
		TimeUtil::Time sStartTime;	// the time when the timer was started
		int iTimeout;				// timeout in ms
		TIMER_VALUES() :
			iTimeout(0)
		{}
	};

	static TimeUtil::Time sCurrentTime;

	// The timers
	typedef std::map<std::string, TIMER_VALUES> MAP_TIMER;
	static MAP_TIMER _mapTimer;

};

/////////////
// Exceptions
class TimerNotSetException : public std::runtime_error {
public:
	// Constructor
	TimerNotSetException(const std::string& message) : runtime_error(message) {
	}
};
