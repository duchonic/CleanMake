#include "logger.h"
#include "customLibs/helper.h"

Logger::Logger(){
	STATE_LOG << "constructor" << '\n';
}

Logger::~Logger(){
	STATE_LOG << "deconstructor" << '\n';
}
