#include "serial.h"
#include "customLibs/helper.h"

#ifdef IS_WINDOWS
	#include <windows.h>
    #include <tchar.h>
#endif

#include <stdio.h>
#include <iostream>

// Constructor
Serial::Serial() {
	CLASS_LOG << "constructor" << '\n';

#ifdef IS_WINDOWS
	hCom = CreateFile(
		pcCommPort, //"\\\\.\\COM10",
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hCom != INVALID_HANDLE_VALUE){
		DCB port{ 0 };
		port.DCBlength = sizeof(port);
		if (GetCommState(hCom, &port)
			&& BuildCommDCB("baud=115200 parity=N data=8 stop=1", &port)
			&& SetCommState(hCom, &port)){
			INFO_LOG << "serial port configured" << '\n';
		}
		else {
			ERROR_LOG << "PROBLEMS WITH SERIAL COM" << '\n';
		}
	}
	else {
		ERROR_LOG << "COM IS NOT VALID" << '\n';
	}
#endif

}

Serial::~Serial() {
	CLASS_LOG << "deconstructor" << '\n';

#ifdef IS_WINDOWS
	CloseHandle(hCom);
#endif

}

void Serial::write(std::string message) {
#ifdef IS_WINDOWS
	WriteFile(
		hCom,
		message.c_str(),
		message.size(),
		&dwRet,
		NULL
	);
#endif
}
