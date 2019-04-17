#include "xmlEventParser.h"
#include "customLibs/helper.h"

// xmlwrapp
#include <xmlwrapp/event_parser.h>

XMLEventParser::XMLEventParser(const char* xmlString){
	if (!parse_chunk(xmlString, strlen(xmlString))) {
		parse_finish();
	}
	parse_finish();
}

XMLEventParser::~XMLEventParser(){
  STATE_LOG << "deconstructor" << '\n';
}

// XML parsing methods
bool XMLEventParser::start_element(const std::string& name, const attrs_type& attrs) {

	DEBUG_LOG << "start_element name=" << name << '\n';

	if (name == ITEM) {
		for (attrs_type::const_iterator ita = attrs.begin(); ita != attrs.end(); ita++) {
			std::string strName = ita->first;
			std::string strValue = ita->second;
			DEBUG_LOG << " " << strName << "=" << strValue;
		}
		DEBUG_LOG << '\n';

		// Destination
		std::string destination = "";
		attrs_type::const_iterator it = attrs.find(ATTR_DESTINATION);
		if (it != attrs.end()) {
			destination = (*it).second;
		}
		DEBUG_LOG << "XMLMessageProcessor destination=" << destination << '\n';

		// Type
		std::string type;
		it = attrs.find(TYPE);
		if (it != attrs.end()) {
			type = (*it).second;
			DEBUG_LOG << "XMLMessageProcessor type=" << type << '\n';

			// Commands
			if (type == TYPE_COMMAND) {
				std::string cmd;
				it = attrs.find(ATTR_COMMAND);
				if (it != attrs.end()) {
					cmd = (*it).second;
					DEBUG_LOG << '\n';
				}
			}

			// Requests
			else if (type == TYPE_REQUEST) {
				// For debug only
				//DEBUG_LOG << "XMLMessageProcessor type request" << '\n';
				std::string req = "";
				it = attrs.find(ATTR_REQUEST);
				if (it != attrs.end()) {
					req = (*it).second;

				}
			}
			else if (type == TYPE_PARAMETER) {
				// For debug only
				//DEBUG_LOG << "XMLMessageProcessor type parameter" << '\n';
			}
		}
	}
	return true;
}

bool XMLEventParser::end_element(const std::string& name) {
	return true;
}

bool XMLEventParser::text(const std::string& contents) {
	return true;
}