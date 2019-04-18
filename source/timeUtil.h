#pragma once

#include <string>
#include <time.h>
#include <stdexcept>


//
// TimeUtil
// Place a description of the class here
//
class TimeUtil {

public:
	// define time representation
	typedef struct timespec Time;

	// Get the current time in milliseconds since pStartTime
	static int getTimeDiff(const Time* pStartTime);

	// Get time diff in mikroseconds
	static int getTimeDiffMikroSec(const Time* pStartTime);

	// Get time diff in milliseconds
	static int getTimeDiff(const Time* pStartTime, const Time* pEndTime);

	// Get the current time since UTC 1/1/1970
	static void getCurrentTime(Time* pTime);

	// Get a formatted date time string
	static char* getCurrentDateTimeString();

	// Get a formatted time string with millisecond accuracy
	static std::string getCurrentMSTimeString();
};

// Exceptions
class BusyWaitOutOfRangeException : public std::out_of_range {
public:
	// Constructor
	BusyWaitOutOfRangeException(const std::string& message)
		: out_of_range(message) {
	}
};
