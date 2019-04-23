#ifndef USB2SPIDRIVER_H
#define USB2SPIDRIVER_H
#include <vector>
#include <stdint.h>
#include "interface/IDriver.h"
#include "interface/ISingleton.h"

struct ftdi_context;
struct mpsse_context;

class USB2SPIDriver: public ISingleton, public IDriver
{
public:
	~USB2SPIDriver();

    // Return the one and only one instance
    static USB2SPIDriver* getInstance();

    // init the driver
    // <<online>>
    void initDriver();

    // do the driver work
    // <<online>>
    void runDriver();

    // reset the drive to a defined state
    // <<offline>>
    void resetDriver();

    // close the driver
    // <<online>>
    void closeDriver();

    void write(const unsigned char* data, int dataSize);
    void purgeReadBuffer();
    void read(unsigned char* data, int dataSize);
    void beginFrame();
    void endFrame();
    bool waitForConversion();

    enum DataBits{
    	SK = 1,
    	DO = 2,
    	DI = 4,
    	CS = 8,
    	GPIO0 = 16,
    	GPIO1 = 32,
    	GPIO2 = 64,
    	GPIO3 = 128
    };

protected:

    USB2SPIDriver();

    // The one and only one instance
    static USB2SPIDriver* _instance;
private:
    void enableSPIMode();
    struct ftdi_context* _ftdi;
    struct mpsse_context* _mpsse;
    std::vector<unsigned char> _outputBuffer;
    unsigned char _defaultPortSettings;
    unsigned char _ioConfig;
	static const int _bufSize = 1024;
	unsigned char _inputBuffer[_bufSize];
};

#endif // USB2SPIDRIVER_H
