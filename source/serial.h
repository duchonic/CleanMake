#pragma once

#ifdef IS_WINDOWS
	#include <windows.h>
#endif

#include <string>

class Serial {

public:

	// constructor
	Serial();
	~Serial();

	bool write(std::string message);

private:

	#ifdef IS_WINDOWS
		DCB dcb;
		HANDLE hCom;
		BOOL fSuccess;
		TCHAR* pcCommPort = TEXT("\\\\.\\COM10"); //
		DWORD dwRet;
	#endif

protected:

};
