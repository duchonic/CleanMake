#pragma once

#include <string>
#include <map>

typedef std::map<std::string, std::string> STRING_MAP;

class IMessage {

public:

	// Destructor
	virtual ~IMessage() {}

    // Return the string representation of the message
    virtual std::string toString() = 0;

	// Add an item
	virtual void addItem(std::string strType, std::string strSource, std::string strDestination, const STRING_MAP& mapAttributes) = 0;
};
