#include "serial.h"
#include "customLibs/helper.h"

Serial::Serial(){
	STATE_LOG << "constructor" << '\n';
}

Serial::~Serial(){
	STATE_LOG << "deconstructor" << '\n';
}
