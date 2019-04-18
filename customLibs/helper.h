#include <iostream>
#include <cstring>

#include "customLibs/timeUtil.h"

#ifdef IS_WINDOWS
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
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
