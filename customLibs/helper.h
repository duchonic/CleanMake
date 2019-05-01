#include <iostream>
#include <cstring>

#include "customLibs/timeUtil.h"


#ifdef IS_MAC
#include <unistd.h>
#elif IS_LINUX
#include <unistd.h>
#else
#include <windows.h>
#endif

#ifdef IS_WINDOWS
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else IS_LINUX
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif


#ifdef IS_MAC
	#define SLEEP_ms(delay_ms) sleep(delay_ms)
#elif IS_LINUX
	#define SLEEP_ms(delay_ms) sleep(delay_ms)
#elif IS_VISUAL_STUDIO
	#define SLEEP_ms(delay_ms) Sleep(delay_ms)
#else
	#define SLEEP_ms(delay_ms) 	Sleep(delay_ms)
#endif


#define DEBUG_LOG (std::cout << "[" << TimeUtil::getCurrentMSTimeString() << "] "  << ":debug: " << __FILENAME__ << ':' << __LINE__ << ' ')
#define INFO_LOG (std::cout <<  "[" << TimeUtil::getCurrentMSTimeString() << "] "  << ":info: " << __FILENAME__ << ':' << __LINE__ << ' ')
#define STATE_LOG (std::cout << "[" << TimeUtil::getCurrentMSTimeString() << "] "  <<  ":state: " << __FILENAME__ << ':' << __LINE__ << ' ')
#define ERROR_LOG (std::cout << "[" << TimeUtil::getCurrentMSTimeString() << "] "  << ":error: " << __FILENAME__ << ':' << __LINE__ << ' ')
#define CLASS_LOG (std::cout << "[" << TimeUtil::getCurrentMSTimeString() << "] "  << ":class: " << __FILENAME__ << ':' << __LINE__ << ' ')
#define TEST_LOG (std::cout << "[" << TimeUtil::getCurrentMSTimeString() << "] "  << ":test: " << __FILENAME__ << ':' << __LINE__ << ' ')


class Helper{

public:
  Helper();
  ~Helper();

private:

};
