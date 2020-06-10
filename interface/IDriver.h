#pragma once

class IDriver {

public:

    // Destructor
	virtual ~IDriver() {};

    // init the driver
    virtual void initDriver() = 0;

    // do the driver work
	virtual void runDriver() = 0;

	// reset the drive to a defined state
	virtual void resetDriver() = 0;

    // close the driver
    virtual void closeDriver() = 0;

};
