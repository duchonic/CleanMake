#include "serial.h"
#include "logger.h"
#include "customLibs/helper.h"

int main(){

	DEBUG_LOG << "main entered" << '\n';

	Logger myLogger;
	Serial mySerial;
	Helper myHelper;

	return 0;
}
