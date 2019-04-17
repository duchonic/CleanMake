#include "XMLMessage.h"

// XML stuff
#include <xmlwrapp/init.h>
#include <xmlwrapp/node.h>
#include <xmlwrapp/attributes.h>

// Constructor
XMLMessage::XMLMessage()
: _strMessage("")
{
    xml::init init;
    _root.set_name("msg");
}

// Constructor
XMLMessage::XMLMessage(std::string strMessage)
: _strMessage(strMessage)
{
    xml::init init;
    _root.set_name("msg");
}

// Destructor
XMLMessage::~XMLMessage() {
}

// Clear all values
void XMLMessage::clear() {
	_strMessage = "";
}


// Sets the message string
void XMLMessage::setMessageString(const std::string& strMessage) {
	_strMessage = strMessage;
}

// Return the string representation of the message
std::string XMLMessage::toString() {

	if (_strMessage != "") {
		return _strMessage;
	}
	std::string str;
	_root.node_to_string(_strMessage);
	return _strMessage;
}

// Add an item
void XMLMessage::addItem(std::string strType, std::string strSource, std::string strDestination) {

    xml::node item("item");
    item.get_attributes().insert("type", strType.c_str());
    item.get_attributes().insert("src", strSource.c_str());
    item.get_attributes().insert("dst", strDestination.c_str());
    _root.push_back(item);
}

// Add an item
void XMLMessage::addItem(std::string strType, std::string strSource, std::string strDestination, const STRING_MAP& mapAttributes) {

    xml::node item("item");
    item.get_attributes().insert("type", strType.c_str());
    item.get_attributes().insert("src", strSource.c_str());
    item.get_attributes().insert("dst", strDestination.c_str());

	for (STRING_MAP::const_iterator it = mapAttributes.begin(); it != mapAttributes.end(); it++) {
		item.get_attributes().insert(((*it).first).c_str(), ((*it).second).c_str());
	}
    _root.push_back(item);
}



