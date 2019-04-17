#pragma once

class IDriver {

public:

    // Destructor
	virtual ~IDriver() {};

    // init the driver
	// <<online>>
    virtual void initDriver() = 0;

    // do the driver work
	// <<online>>
	virtual void runDriver() = 0;

	// reset the drive to a defined state
	// <<offline>>
	virtual void resetDriver() = 0;

    // close the driver
	// <<online>>
    virtual void closeDriver() = 0;

};
