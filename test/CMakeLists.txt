add_executable (
	testing
	catchMain.cpp
	catchSerial.cpp
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
		"C:/cLibs/LibMPSSE-SPI/lib/windows/i386/libMPSSE.lib"
		"C:/cLibs/LibMPSSE-I2C/lib/windows/i386/libMPSSE.lib"
		LibXml2
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
