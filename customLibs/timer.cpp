#include "timer.h"

#include <string>

Timer::MAP_TIMER Timer::_mapTimer;

void Timer::startTimer(const std::string& timerID, unsigned int timeMilliSeconds)
{
	TIMER_VALUES timer;
	TimeUtil::getCurrentTime(&(timer.sStartTime));
	timer.iTimeout = timeMilliSeconds;
	_mapTimer[timerID] = timer;
}

void Timer::restartTimer(const std::string& timerID)
{
	MAP_TIMER::iterator it = _mapTimer.find(timerID);
	if(it == _mapTimer.end())
		throw TimerNotSetException(std::string("Timer ") + timerID + std::string(" is not set."));
	TimeUtil::getCurrentTime(&(it->second.sStartTime));
}

bool Timer::isTimerSet(const std::string& timerID)
{
	MAP_TIMER::iterator it = _mapTimer.find(timerID);
	if(it != _mapTimer.end())
		return true;
	else
		return false;
}

bool Timer::timeReached(const std::string& timerID)
{
	if(!isTimerSet(timerID))
		return false;
	TIMER_VALUES* timer = &(_mapTimer[timerID]);
	return TimeUtil::getTimeDiff(&(timer->sStartTime)) >= timer->iTimeout;
}

int Timer::getTime(const std::string& timerID)
{
	if(!isTimerSet(timerID))
		throw TimerNotSetException(std::string("Timer ") + timerID + std::string(" is not set."));
	return TimeUtil::getTimeDiff(&(_mapTimer[timerID].sStartTime));
}

int Timer::getTimeUs(const std::string& timerID)
{
	return getTime(timerID) * 1000;
}

void Timer::removeTimer(const std::string& timerID)
{
	MAP_TIMER::iterator it = _mapTimer.find(timerID);
	if(it != _mapTimer.end())
		_mapTimer.erase(it);
}
