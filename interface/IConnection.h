#pragma once

#include <string>

class IConnection {

public:

    // Destructor
    virtual ~IConnection() {}

    // initialize
    virtual void initialize()  = 0;

	// connect
	virtual bool connect() = 0;

	// disconnect
	virtual void disconnect() = 0;

	// Check for data
	virtual bool canReceiveData() = 0;

	// Receive data
	virtual bool receiveData(std::string& strData) = 0;

	// send data
	virtual bool sendData(const std::string& strData) = 0;

};
