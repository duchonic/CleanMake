#pragma once

#ifdef IS_MAC

#else
	#include <xmlwrapp/event_parser.h>
#endif

#include <string>

// Constants used for parsing
static const std::string DESTINATION_SYS = "sys";
static const std::string DESTINATION_BROADCAST = "broadcast";

// Types
static const std::string ITEM = "item";
static const std::string MESSAGE = "msg";
static const std::string TYPE = "type";

// Types
static const std::string TYPE_REQUEST = "request";
static const std::string TYPE_COMMAND = "command";
static const std::string TYPE_ERROR = "error";
static const std::string TYPE_MESSAGE = "message";
static const std::string TYPE_STATE = "state";
static const std::string TYPE_ALARM = "alarm";
static const std::string TYPE_DATA = "data";
static const std::string TYPE_PARAMETER = "parameter";
static const std::string TYPE_VERSION = "version";
static const std::string TYPE_WATCHDOG = "watchdog";
static const std::string TYPE_LOG = "log";

// Attributes
static const std::string ATTR_REQUEST = "req";
static const std::string ATTR_COMMAND = "cmd";
static const std::string ATTR_PARAM = "param";
static const std::string ATTR_ERROR = "error";
static const std::string ATTR_MESSAGE = "msg";
static const std::string ATTR_DESTINATION = "dst";
static const std::string ATTR_SOURCE = "src";
static const std::string ATTR_STATE = "state";
static const std::string ATTR_SUBSTATE = "substate";
static const std::string ATTR_ALARM_ID = "id";
static const std::string ATTR_ALARM_CATEGORY = "cat";
static const std::string ATTR_ALARM_INFO = "info";

// Recurrence
static const std::string ATTR_RECURRENCE = "recurr";
static const std::string RECURRENCE_ONCHANGE = "onchange";
static const std::string RECURRENCE_OFF = "off";
static const std::string RECURRENCE_NOW = "now";

// Requests
static const std::string REQUEST_MESSAGE = "message";
static const std::string REQUEST_STATE = "state";
static const std::string REQUEST_DATA = "data";
static const std::string REQUEST_ALARM = "alarm";
static const std::string REQUEST_PARAMETER = "parameter";
static const std::string REQUEST_VERSION = "version";
static const std::string REQUEST_WATCHDOG = "watchdog";

// Data subtype
static const std::string DATA_SUBTYPE = "subtype";
static const std::string DATA_SUBTYPE_INTENSITY = "intensity";
static const std::string DATA_SUBTYPE_SCAN = "scan";
static const std::string DATA_SUBTYPE_ADJUST = "adjust";
static const std::string DATA_SUBTYPE_STATISTICS = "statistic";

#ifdef IS_MAC
	class XMLEventParser  {
#else
	class XMLEventParser : public xml::event_parser {
#endif

public:
	XMLEventParser(const char* xmlString);
	~XMLEventParser();

protected:
#ifdef IS_MAC

#else
	virtual bool start_element(const std::string& name, const attrs_type& attrs);
	virtual bool end_element(const std::string& name);
	virtual bool text(const std::string& contents);
#endif

private:

};
