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

	#ifdef IS_VISUAL_STUDIO
		DCB dcb;
		HANDLE hCom;
		BOOL fSuccess;
		TCHAR* pcCommPort = TEXT("\\\\.\\COM10"); //
		DWORD dwRet;
	#elif IS_LINUX
		
	#else
		DCB dcb;
		HANDLE hCom;
		BOOL fSuccess;
		TCHAR* pcCommPort = NULL; //TEXT("./COM10"); //
		DWORD dwRet;
	#endif


protected:

};
