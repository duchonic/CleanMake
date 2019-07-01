add_executable (
	testing
	catchMain.cpp
	catchSerial.cpp
	catchDriver.cpp
	catchInterface.cpp
	#catchFTDI.cpp
	catchClassLogger.cpp
	catchCleverLogger.cpp
	catchMisc.cpp
	catchTryCatch.cpp
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
		"${PROJECT_SOURCE_DIR}/winLibs/libMPSSE/SPI/libMPSSE.lib"
		"${PROJECT_SOURCE_DIR}/winLibs/libMPSSE/I2C/libMPSSE.lib"
		wsock32
		ws2_32
	)
else()
	target_link_libraries (
		demo
		LINK_PUBLIC
		Source
		Factory
		CustomLib
		Communication
		Collector
	)
endif()
