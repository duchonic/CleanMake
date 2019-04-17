#pragma once

#include "interface/IMessage.h"
#include "interface/IDriver.h"

//
// IOperation
//
class IOperation : public IDriver {

public:

	// Destructor
	virtual ~IOperation() {}

	// hasMessageArrived
	// <<offline>>
    virtual bool hasMessageArrived() const = 0;

    // getMessage
	// <<offline>>
    virtual IMessage* getMessage() = 0;

    // sendMessage
	// <<offline>>
    virtual void sendMessage(IMessage* pMessage) = 0;

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
