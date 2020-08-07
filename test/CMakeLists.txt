add_executable (
	testing
	catchMain.cpp
	#catchStateMachine.cpp
	#catchClass.cpp
	#catchSerial.cpp
	#catchDriver.cpp
	#catchInterface.cpp
	#catchTimer.cpp
	#catchThread.cpp
	#catchVirtual.cpp
	#catchJson.cpp
	catchRecursion.cpp
	catchToString.cpp

)

if (WIN32)
	message(STATUS "Testing Libs")
	
	target_link_libraries (
		testing
		LINK_PUBLIC
		Source
		Factory
		CustomLib
		Communication
		Collector
		wsock32
		ws2_32
		Lightsource
		FWProfile
	)
else()
	target_link_libraries (
		testing
		LINK_PUBLIC
		Source
		Factory
		CustomLib
		Communication
		Collector
		Lightsource
		FWProfile
	)
endif()
