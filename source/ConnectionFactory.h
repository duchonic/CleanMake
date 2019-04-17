#pragma once

#include "interface/IConnection.h"

#include <stdexcept>

//
// ConnectionFactory
// Get different kinds of connections
// @author Peter Hug
//
class ConnectionFactory {

public:

	// Get the requested driver
	static IConnection* getConnection(const std::string& strDriverID);

    // Destructor
    virtual ~ConnectionFactory();

protected:
    // Constructor
    ConnectionFactory();
};

/////////////
// Exceptions
class InvalidConnectionException: public std::invalid_argument {
	public:
		// Constructor
		InvalidConnectionException(const std::string& message)
			: invalid_argument(message) {
		}
};

