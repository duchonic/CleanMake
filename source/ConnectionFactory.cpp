#include "ConnectionFactory.h"

// connections
#include <SocketConnection.h>

// Logger
#include <Logger.h>

// Constructor
ConnectionFactory::ConnectionFactory() {
}

// Destructor
ConnectionFactory::~ConnectionFactory() {
}

IConnection* ConnectionFactory::getConnection(const std::string& strDriverID) {
	if (strDriverID == "SocketConnection") {
		return SocketConnection::getInstance();
	}
	return NULL;
}
