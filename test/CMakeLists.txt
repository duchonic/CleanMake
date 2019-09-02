add_executable (
	testing
	catchMain.cpp
	catchSerial.cpp
	catchDriver.cpp
	catchInterface.cpp
	catchTimer.cpp
	catchThread.cpp
)

if (WIN32)
	message(STATUS "Testing Libraries")
	
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
	)
endif()
