#include <iostream>
#include <cstring>

#ifdef IS_WINDOWS
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define DEBUG_LOG (std::cout << ":debug: " << __FILENAME__ << '/' << __LINE__ << ' ')
#define INFO_LOG (std::cout << ":info: " << __FILENAME__ << '/' << __LINE__ << ' ')
#define STATE_LOG (std::cout << ":state: " << __FILENAME__ << '/' << __LINE__ << ' ')
#define ERROR_LOG (std::cout << ":error: " << __FILENAME__ << '/' << __LINE__ << ' ')

class Helper{

public:
  Helper();
  ~Helper();
  const int DATE = 2019;

private:

};
