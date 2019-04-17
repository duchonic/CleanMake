#pragma once

// Tools
#include "interface/ISingleton.h"
#include "interface/IMessage.h"
#include "interface/IOperation.h"

#include <vector>

class IConnection;

class SysOperation : public IOperation, public ISingleton {

public:

    // Return the one and only one instance
    static SysOperation* getInstance();

    // Destructor
    virtual ~SysOperation();

    // hasMessageArrived
	// <<offline>>
    virtual bool hasMessageArrived() const;

    // getMessage
	// <<offline>>
    virtual IMessage* getMessage();

    // sendMessage
	// <<offline>>
    virtual void sendMessage(IMessage* pMessage);

    // init the driver
	// <<online>>
    virtual void initDriver();

    // do the driver work
	// <<online>>
	virtual void runDriver();

	// reset the drive to a defined state
	// <<offline>>
	virtual void resetDriver();

    // close the driver
	// <<online>>
    virtual void closeDriver();

protected:

    // Constructor
    // protected because of singleton implementation
    SysOperation();

    // The one and only one instance
    static SysOperation* _instance;

private:

	// Flag
	bool _bMessageArrived;

	// received message
	std::string _messageString;

	// Messages to send
	std::vector<IMessage*> _vecMessages;

	// The connection
	IConnection* _pConnection;
};
