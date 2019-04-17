#pragma once

#include "interface/IMessage.h"
#include <xmlwrapp/node.h>

//
// XMLMessage
// Place a description of the class here
//
class XMLMessage : public IMessage {

public:

    // Constructor
    XMLMessage();

    // Constructor
    XMLMessage(std::string strMessage);

    // Destructor
    virtual ~XMLMessage();

	// Clear all values
	void clear();

    // Sets the message string
    virtual void setMessageString(const std::string& strMessage);

    // Return the string representation of thge message
    virtual std::string toString();

	// Add an item
	virtual void addItem(std::string strType, std::string strSource, std::string strDestination);
	virtual void addItem(std::string strType, std::string strSource, std::string strDestination, const STRING_MAP& mapAttributes);

private:

	// XML stuff
    xml::node _root;

	// message string
	std::string _strMessage;
};
