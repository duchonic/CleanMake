#include <iostream>

//#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define DEBUG_LOG (std::cout << ":debug: " << __FILENAME__ << '/' << __LINE__ << ' ')
#define STATE_LOG (std::cout << ":state: " << __FILENAME__ << '/' << __LINE__ << ' ')

class Helper{

public:
  Helper();
  ~Helper();
  const int DATE = 2019;

private:

};
