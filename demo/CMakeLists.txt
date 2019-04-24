# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (demo demo.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo

if (WIN32)
	message(STATUS "Search Windows libraries")
	find_library(WSOCK32_LIBRARY wsock32)
  find_library(WS2_32_LIBRARY ws2_32)
	find_package(LibXml2 REQUIRED)
	message(STATUS "Add windows libraries")
	target_link_libraries (
		demo
		LINK_PUBLIC
		Source
		Factory
		CustomLib
		Communication
		Collector
		"C:/cLibs/xmlwrapp/lib/xmlwrapp.lib"
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
