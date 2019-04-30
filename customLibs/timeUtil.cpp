#include "timeUtil.h"
#include <stdlib.h>

#ifdef IS_LINUX
	#include <sys/time.h>
#elif IS_MAC

#else
	#include <sys/utime.h>
#endif

#include <sstream>

#include <iomanip>

#ifdef IS_WINDOWS
	#include <windows.h>
	#define CLOCK_REALTIME 0
	/* FILETIME of Jan 1 1970 00:00:00. */
	static const unsigned __int64 epoch = ((unsigned __int64)116444736000000000ULL);
#endif

int TimeUtil::getTimeDiff(const Time* pStartTime)
{
	Time currentTime;
	getCurrentTime(&currentTime);
	return getTimeDiff(pStartTime, &currentTime);
}

int TimeUtil::getTimeDiffMikroSec(const Time* pStartTime)
{
	return getTimeDiff(pStartTime) * 1000;
}

int TimeUtil::getTimeDiff(const Time* pStartTime, const Time* pEndTime)
{
    timespec temp;
    if ((pEndTime->tv_nsec-pStartTime->tv_nsec)<0) {
        temp.tv_sec = pEndTime->tv_sec-pStartTime->tv_sec-1;
        temp.tv_nsec = 1000000000+pEndTime->tv_nsec-pStartTime->tv_nsec;
    } else {
        temp.tv_sec = pEndTime->tv_sec-pStartTime->tv_sec;
        temp.tv_nsec = pEndTime->tv_nsec-pStartTime->tv_nsec;
    }
    return (temp.tv_sec * 1000) + (temp.tv_nsec / 1000000LL);
}

/*
  just do this in the windows visual studio version
 */
#ifdef IS_WINDOWS
int clock_gettime(int, struct timespec* spec)      //C-file part
{
	__int64 wintime;
	GetSystemTimeAsFileTime((_FILETIME*)& wintime);
	wintime -= epoch;				//1jan1601 to 1jan1970
	spec->tv_sec = wintime / 10000000i64;           //seconds
	spec->tv_nsec = wintime % 10000000i64 * 100;    //nano-seconds
	return 0;
}
#endif

void TimeUtil::getCurrentTime(Time* pTime)
{
	clock_gettime(CLOCK_REALTIME, pTime);
}

char* TimeUtil::getCurrentDateTimeString()
{
	static char timeString[255];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(timeString, "%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return timeString;
}

/*
 just do this in the windows visual studio version
*/
#ifdef IS_WINDOWS
int gettimeofday(struct timeval* tp, struct timezone* tzp)
{
	FILETIME    file_time;
	SYSTEMTIME  system_time;
	ULARGE_INTEGER ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp->tv_sec = (long)((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);

	return 0;
}
#endif

std::string TimeUtil::getCurrentMSTimeString()
{

#ifdef IS_LINUX
	static char timeString[255];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	sprintf(timeString, "%02d:%02d:%02d:%03d", tm.tm_hour, tm.tm_min, tm.tm_sec, (int)(tv.tv_usec / 1000));
	return timeString;
#elif IS_WINDOWS
	std::stringstream timeStream;
	SYSTEMTIME st;
	GetLocalTime(&st);
	timeStream << std::setfill('0') << std::setw(2) << st.wHour   << ':';
	timeStream << std::setfill('0') << std::setw(2) << st.wMinute << ':';
	timeStream << std::setfill('0') << std::setw(2) << st.wSecond ;
	return timeStream.str();
#elif IS_MAC
    static char timeString[255];
    //time_t t = time(NULL);
    //struct tm tm = *localtime(&t);
    //struct timeval  tv;
    //gettimeofday(&tv, NULL);
    //sprintf(timeString, "%02d:%02d:%02d:%03d", tm.tm_hour, tm.tm_min, tm.tm_sec, (int)(tv.tv_usec / 1000));
    return timeString;
#endif

}
