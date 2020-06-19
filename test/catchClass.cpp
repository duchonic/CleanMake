// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"

class RateFromExtrema {
  public:
    RateFromExtrema()
    {
      DEBUG_LOG << "constructor" << std::endl;
    };
    ~RateFromExtrema() 
    {
      DEBUG_LOG << "deconstructor" << std::endl;
    };

    bool calcNewRate() const {
      return true;
    }

    void setRate(double newRate) {
      INFO_LOG << "set new rate to: " << newRate << std::endl;
    };
    double getRate(void) {
      return 0;
    }
  
  
  protected:

  private:
    int iTime;
};


